import asyncio
import websockets
import json

async def send_command(websocket, direction, speed):
    # Prepare JSON command
    command = json.dumps({"direction": direction, "speed": speed})
    await websocket.send(command)
    print(f"Sent: {command}")

async def main():
    uri = "ws://192.168.165.149:81"  # Replace XX with ESP8266 IP
    async with websockets.connect(uri) as websocket:
        for i in range(100):
            await send_command(websocket, "FWD", i)  # Example command
            await asyncio.sleep(0)  # Non-blocking delay

# Run the client
asyncio.get_event_loop().run_until_complete(main())
