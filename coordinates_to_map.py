import asyncio
from bleak import BleakClient, BleakScanner
import plotly.graph_objs as go
import plotly.offline as pyo
from scipy.spatial import ConvexHull

SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8"
TARGET_NAME = "ESP32_UART_BLE"

coords = []

def notification_handler(sender, data: bytearray):
    if len(data) == 4:  # X and Y coordinates (2 byteseach)
        x = int.from_bytes(data[0:2], byteorder='big', signed=True)
        y = int.from_bytes(data[2:4], byteorder='big', signed=True)
        coords.append((x, y))
        print(f"Received coordinate {len(coords)}: X={x}, Y={y}")

async def main():
    # Device discovery
    device = await BleakScanner.find_device_by_name(TARGET_NAME)
    if not device:
        print("ESP32 not found!")
        return

    async with BleakClient(device) as client:
        print("Connected to ESP32")
        
        # User confirmation
        if input("Start navigation? (y/n) ").lower() != 'y':
            return
            
        # Get coordinate count
        while True:
            try:
                count = int(input("How many coordinates to collect (1-255)? "))
                if 1 <= count <= 255:
                    break
                print("Please enter between 1-255")
            except ValueError:
                print("Invalid number")
        
        # Send start command with count
        await client.write_gatt_char(CHARACTERISTIC_UUID, f"start:{count}".encode())
        print(f"Requesting {count} coordinates...")
        

        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)

        while len(coords) < count:
            await asyncio.sleep(0.1)
            print(f"Progress: {len(coords)}/{count}", end='\r')
            
        print(f"\nReceived all {count} coordinates!")
        await client.stop_notify(CHARACTERISTIC_UUID)

    if coords:
        xs, ys = zip(*coords)
        
        fig_points = go.Figure()
        fig_points.add_trace(go.Scatter(x=xs, y=ys,
                                        mode='markers',
                                        marker=dict(color='blue', size=8),
                                        name='Received Coordinates'))

        fig_points.update_layout(title='Received Coordinates',
                                 xaxis_title='X',
                                 yaxis_title='Y',
                                 template='plotly_white')

        html_points_file = "coordinates_points.html"
        pyo.plot(fig_points, filename=html_points_file, auto_open=True)
        print(f"Points plot saved to {html_points_file}")

        if len(coords) >= 3:
            try:
                fig_shape = go.Figure()
                
                hull = ConvexHull(coords)
                hull_points = [coords[i] for i in hull.vertices]
                hull_xs, hull_ys = zip(*hull_points)

                hull_xs += (hull_xs[0],)
                hull_ys += (hull_ys[0],)
                
                fig_shape.add_trace(go.Scatter(x=hull_xs, y=hull_ys,
                                               mode='lines',
                                               fill='toself',
                                               fillcolor='rgba(0,100,80,0.2)',
                                               line=dict(color='green', width=2),
                                               name='Room Shape'))

                fig_shape.update_layout(title='Room Shape',
                                        xaxis_title='X',
                                        yaxis_title='Y',
                                        template='plotly_white')

                html_shape_file = "room_shape.html"
                pyo.plot(fig_shape, filename=html_shape_file, auto_open=True)
                print(f"Room shape plot saved to {html_shape_file}")

            except Exception as e:
                print(f"Nu s-a putut calcula poligonul convex: {e}")

asyncio.run(main())