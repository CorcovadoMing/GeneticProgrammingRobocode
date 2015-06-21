__author__ = 'Ming'

from shell import *
import pika
import os

def compile_robot():
    out, err = shell_command(["javac", "-cp", "/robocode/libs/robocode.jar", "robots/GP/GP.java"])
    print out, err

def simulate(num):
    out, err = shell_command(["/robocode/robocode.sh", "-battle", "/source/ControlEngine/battle/gp"+str(num)+".battle", "-nodisplay", "-results",
                              "/source/ControlEngine/result/result.txt"])
    return parse_result("result/result.txt")


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

def fitness(records, type):
    result = 0
    print records

    survive0 = int(records[0]['survival']) + int(records[0]['survival_bonus'])
    bullet0 = int(records[0]['bullet']) + int(records[0]['bullet_bonus'])
    ram0 = int(records[0]['ram']) + int(records[0]['ram_bonus'])

    survive1 = int(records[1]['survival']) + int(records[1]['survival_bonus'])
    bullet1 = int(records[1]['bullet']) + int(records[1]['bullet_bonus'])
    ram1 = int(records[1]['ram']) + int(records[1]['ram_bonus'])

    if int(type) == 0:
        if "GP" in records[0]['name']:
            result = (0.6*survive0 + 0.2*bullet0 + 0.2*ram0 + 0.00001)/(0.6*survive0 + 0.2*bullet0 + 0.2*ram0 + 0.6*survive1 + 0.2*bullet1 + 0.2*ram1 + 0.00001)
        else:
            result = (0.6*survive1 + 0.2*bullet1 + 0.2*ram1 + 0.00001)/(0.6*survive0 + 0.2*bullet0 + 0.2*ram0 + 0.6*survive1 + 0.2*bullet1 + 0.2*ram1 + 0.00001)
    elif int(type) == 1:
        if "GP" in records[0]['name']:
            result = (0.2*survive0 + 0.6*bullet0 + 0.2*ram0 + 0.00001)/(0.2*survive0 + 0.6*bullet0 + 0.2*ram0 + 0.2*survive1 + 0.6*bullet1 + 0.2*ram1 + 0.00001)
        else:
            result = (0.2*survive1 + 0.6*bullet1 + 0.2*ram1 + 0.00001)/(0.2*survive0 + 0.6*bullet0 + 0.2*ram0 + 0.2*survive1 + 0.6*bullet1 + 0.2*ram1 + 0.00001)
    else:
        if "GP" in records[0]['name']:
            result = (0.2*survive0 + 0.2*bullet0 + 0.6*ram0 + 0.00001)/(0.2*survive0 + 0.2*bullet0 + 0.6*ram0 + 0.2*survive1 + 0.2*bullet1 + 0.6*ram1 + 0.00001)
        else:
            result = (0.2*survive1 + 0.2*bullet1 + 0.6*ram1 + 0.00001)/(0.2*survive0 + 0.2*bullet0 + 0.6*ram0 + 0.2*survive1 + 0.2*bullet1 + 0.6*ram1 + 0.00001)

    return result

def serve():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host=os.environ['RABBITMQ_PORT_5672_TCP_ADDR']))
    channel = connection.channel()

    channel.exchange_declare(exchange='control', type='fanout')
    result = channel.queue_declare(exclusive=True)
    queue_name = result.method.queue
    channel.queue_bind(exchange='control', queue=queue_name)

    def callback(ch, method, properties, body):
        compile_robot()
        message = str((fitness(simulate(1), body) + fitness(simulate(2), body) + fitness(simulate(3), body) + fitness(simulate(4), body) + fitness(simulate(5), body))/float(5))
        connection = pika.BlockingConnection(pika.ConnectionParameters(host=os.environ['RABBITMQ_PORT_5672_TCP_ADDR']))
        channel = connection.channel()
        channel.exchange_declare(exchange='gp', type='fanout')
        channel.basic_publish(exchange='gp', routing_key='', body=message)

    channel.basic_consume(callback, queue=queue_name, no_ack=True)
    channel.start_consuming()


if __name__ == '__main__':
    serve()
