__author__ = 'Ming'

from shell import *
import pika

def simulate():
    out, err = shell_command(["D:\\Robocode\\robocode.bat", "-battle", "battle\\intro.battle", "-nodisplay", "-results",
                              "result\\result.txt"])
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


def serve():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))
    channel = connection.channel()

    channel.exchange_declare(exchange='control', type='fanout')
    result = channel.queue_declare(exclusive=True)
    queue_name = result.method.queue
    channel.queue_bind(exchange='control', queue=queue_name)

    def callback(ch, method, properties, body):
        print " [x] %r" % (body,)
        connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))
        channel = connection.channel()
        channel.exchange_declare(exchange='gp', type='fanout')
        message = "TEST"
        channel.basic_publish(exchange='gp', routing_key='', body=message)
        print " [x] Sent %r" % (message,)
        connection.close()

    channel.basic_consume(callback, queue=queue_name, no_ack=True)
    channel.start_consuming()


if __name__ == '__main__':
    serve()
