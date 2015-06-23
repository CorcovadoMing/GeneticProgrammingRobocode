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

def fitness(records, body):
    result = 0
    print records

    survive0 = int(records[0]['survival']) + int(records[0]['survival_bonus'])
    bullet0 = int(records[0]['bullet']) + int(records[0]['bullet_bonus'])
    ram0 = int(records[0]['ram']) + int(records[0]['ram_bonus'])

    survive1 = int(records[1]['survival']) + int(records[1]['survival_bonus'])
    bullet1 = int(records[1]['bullet']) + int(records[1]['bullet_bonus'])
    ram1 = int(records[1]['ram']) + int(records[1]['ram_bonus'])

    if "0" in body:
        print 'Type 0 detect!'
        if "GP" in records[0]['name']:
            result = (0.6*survive0 + 0.2*bullet0 + 0.2*ram0 + 0.00001)/(0.6*survive0 + 0.2*bullet0 + 0.2*ram0 + 0.6*survive1 + 0.2*bullet1 + 0.2*ram1 + 0.00001)
        else:
            result = (0.6*survive1 + 0.2*bullet1 + 0.2*ram1 + 0.00001)/(0.6*survive0 + 0.2*bullet0 + 0.2*ram0 + 0.6*survive1 + 0.2*bullet1 + 0.2*ram1 + 0.00001)
    elif "1" in body:
        print 'Type 1 detect!'
        if "GP" in records[0]['name']:
            result = (0.2*survive0 + 0.6*bullet0 + 0.2*ram0 + 0.00001)/(0.2*survive0 + 0.6*bullet0 + 0.2*ram0 + 0.2*survive1 + 0.6*bullet1 + 0.2*ram1 + 0.00001)
        else:
            result = (0.2*survive1 + 0.6*bullet1 + 0.2*ram1 + 0.00001)/(0.2*survive0 + 0.6*bullet0 + 0.2*ram0 + 0.2*survive1 + 0.6*bullet1 + 0.2*ram1 + 0.00001)
    else:
        print 'Type 2 detect'
        if "GP" in records[0]['name']:
            result = (0.2*survive0 + 0.2*bullet0 + 0.6*ram0 + 0.00001)/(0.2*survive0 + 0.2*bullet0 + 0.6*ram0 + 0.2*survive1 + 0.2*bullet1 + 0.6*ram1 + 0.00001)
        else:
            result = (0.2*survive1 + 0.2*bullet1 + 0.6*ram1 + 0.00001)/(0.2*survive0 + 0.2*bullet0 + 0.6*ram0 + 0.2*survive1 + 0.2*bullet1 + 0.6*ram1 + 0.00001)

    return result

print str(fitness(parse_result("result/result.txt"), "0")/float(1))