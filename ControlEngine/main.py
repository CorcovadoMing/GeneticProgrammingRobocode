__author__ = 'Ming'

from shell import *


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
    records = parse_result("result.txt")
    for tank in records:
        print tank

    out, err = shell_command(["ls", "-al"])
    print out


