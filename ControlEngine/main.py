__author__ = 'Ming'

from shell import *
import pika
import time


def simulate():
    out, err = shell_command(["D:\\Robocode\\robocode.bat", "-battle", "battle\\intro.battle", "-nodisplay", "-results", "result\\result.txt"])
    print out
    return parse_result("result\\result.txt")


def parse_result(filename):
    skip = 2
    records = []
    process_file = open(filename, 'r')
    for line in process_file.readlines():
        if skip != 0:
            skip -= 1
            continue
        else:
            tank = {}
            tank["name"] = line.split('\t')[0]
            tank["score"] = line.split('\t')[1]
            tank["survival"] = line.split('\t')[2]
            tank["survival_bonus"] = line.split('\t')[3]
            tank["bullet"] = line.split('\t')[4]
            tank["bullet_bonus"] = line.split('\t')[5]
            tank["ram"] = line.split('\t')[6]
            tank["ram_bonus"] = line.split('\t')[7]
            records.append(tank)
    process_file.close()
    return records

if __name__ == '__main__':
    connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))
    channel = connection.channel()

    channel.queue_declare(queue='robocode_queue', durable=True)
    print ' [*] Waiting for messages. To exit press CTRL+C'

    def callback(ch, method, properties, body):
        print " [x] Received %r" % (body,)
        if str(body) == "simulate":
            records = simulate()
            for tank in records:
                print tank
        time.sleep(body.count('.'))
        print " [x] Done"
        ch.basic_ack(delivery_tag=method.delivery_tag)

    channel.basic_qos(prefetch_count=1)
    channel.basic_consume(callback, queue='robocode_queue')
    channel.start_consuming()
