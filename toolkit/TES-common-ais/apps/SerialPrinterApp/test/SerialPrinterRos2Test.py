#!/usr/bin/env python3
"""Host-only process/topic regression checks; requires built ROS2 interfaces."""
import os
import signal
import subprocess
import sys
import tempfile
import time
from pathlib import Path

import rclpy
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy
from cpm_common_interfaces.msg import SerialPrinterRequest


def main():
    binary = sys.argv[1]
    rclpy.init()
    node = rclpy.create_node('serial_printer_regression')
    publisher = node.create_publisher(
        SerialPrinterRequest, 'serial_printer_request',
        QoSProfile(depth=2, reliability=ReliabilityPolicy.RELIABLE,
                   durability=DurabilityPolicy.VOLATILE))
    cases = [(b'line', 1, b'line\n\f'),
             (b'a\r\nb\n\nc\r', 2, b'a\r\nb\n\nc\r\n\f' * 2),
             (b'copies', 255, b'copies\n\f' * 3),
             (b'zero', 0, b''), (b'', 1, b'')]
    with tempfile.TemporaryDirectory() as directory:
        for index, (text, copies, expected) in enumerate(cases):
            path = Path(directory) / 'print.txt'
            path.write_bytes(text)
            process = subprocess.Popen(
                [binary, '--instance', 'SerialPrinterApp', '--ros-args',
                 '-p', 'scheduler:=SCHED_OTHER', '-p', 'scheduler_priority:=0',
                 '-p', 'seconds_between_docs:=0.0', '-p', 'baud_rate:=115200'],
                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            try:
                deadline = time.monotonic() + 10
                while publisher.get_subscription_count() == 0:
                    assert process.poll() is None, 'Printer exited during startup'
                    assert time.monotonic() < deadline, 'No subscriber discovered'
                    rclpy.spin_once(node, timeout_sec=0.05)
                publisher.publish(SerialPrinterRequest(
                    command=SerialPrinterRequest.PRINT, file_path=str(path),
                    number_of_copies=copies))
                time.sleep(1.2)
                process.send_signal(signal.SIGTERM)
                output, errors = process.communicate(timeout=5)
                assert process.returncode == 0, errors.decode(errors='replace')
                assert output == expected, (index, output, expected)
            finally:
                if process.poll() is None:
                    process.kill()
                    process.communicate()
            # Allow DDS discovery to remove the old subscriber before the next process.
            deadline = time.monotonic() + 5
            while publisher.get_subscription_count() and time.monotonic() < deadline:
                rclpy.spin_once(node, timeout_sec=0.05)
        print('PASS: 5 stdout topic cases, copy cap, zero/empty, CR/LF and SIGTERM cleanup')
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
