import asyncio
from bleak import BleakClient, BleakScanner
import plotly.graph_objs as go
import plotly.offline as pyo

SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8"
TARGET_NAME = "ESP32_UART_BLE"

coords = []

def notification_handler(sender, data: bytearray):
    if len(data) == 4:  # X and Y coordinates (2 bytes each)
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

        
        # Setup notifications

        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)   
        # Wait for all coordinates
        while len(coords) < count:
            await asyncio.sleep(0.1)
            print(f"Progress: {len(coords)}/{count}", end='\r')

         
        
        print(f"\nReceived all {count} coordinates!")
        await client.stop_notify(CHARACTERISTIC_UUID)

     # Generate Plotly figure
    xs, ys = zip(*coords)

    fig = go.Figure()

    fig.add_trace(go.Scatter(x=xs, y=ys,
                             mode='markers+lines',
                             marker=dict(color='blue', size=8),
                             line=dict(color='red', dash='dash'),
                             name='Path'))

    fig.update_layout(title='Received Coordinates',
                      xaxis_title='X',
                      yaxis_title='Y',
                      template='plotly_white')

    # Save to HTML file
    html_file = "coordinates_map.html"
    pyo.plot(fig, filename=html_file, auto_open=True)
    print(f"Map saved to {html_file}")

asyncio.run(main())