import os
import sys
import socket
import re
from pathlib import Path

IP = 'localhost'
PORT = 6454 # constant value for art-net communication
# hardcoded path to file containing artnet replies
reply1 = Path("splayArtReply.bin")
reply2 = Path("octoArtReply.bin")

def get_artnet_data(path_to_file: Path) -> bytes:
    """Reads artnet data from file and returns it as bytes"""
    # actual artnet data starts at byte 42
    artnet_payload_offset = 42
    with open(path_to_file, 'rb') as data:
        reply = data.read()
    return reply[artnet_payload_offset:]

if __name__ == '__main__':
    try:
        ip_address = sys.argv[1]
    except IndexError:
        print("No argument was provided. Correct usage:"\
            "python sendartmessages.py <ip address>")
        quit()
    ip_pattern = re.compile("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$")
    if not ip_pattern.match(ip_address):
        print("invalid ip address")
        quit()
    # create udp socket
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # send packets
    for reply in [reply1, reply2]:
        udp_socket.sendto(get_artnet_data(reply), (ip_address, PORT))
