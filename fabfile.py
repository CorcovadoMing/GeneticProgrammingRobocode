from __future__ import with_statement
from fabric.api import local
from fabric.colors import green, magenta, yellow
from fabric.context_managers import hide
import time

container = [
'rf37535/rabbitmq',
'rf37535/dummy',
'rf37535/robocode:controlengine'
]

container_name = [
'rabbitmq',
'robocode-source',
'controlengine',
]

startup_command = [
'docker run -d --name rabbitmq rf37535/rabbitmq',
'docker create -v /e/Github/GeneticProgrammingRobocode:/source --name robocode-source rf37535/dummy',
'docker run -d --name controlengine --volumes-from robocode-source --link rabbitmq:rabbitmq rf37535/robocode:controlengine bash -c "cd /source/ControlEngine && python main.py"'
]

def up():
    with hide('running'):
        for i in xrange(len(container)):
            print magenta('['+str(i+1)+'/'+str(len(container))+'] Start up '+container_name[i]+'...', bold=True)
            print green(local(startup_command[i], capture=True))
            if i == 0:
                for wait in xrange(5, 0, -1):
                    print yellow('[info] Wait '+str(wait)+' second for service ' + container_name[i])
                    time.sleep(1)

def ps(state='run'):
    with hide('running'):
        if state == 'all':
            print magenta("[All process state]", bold=True)
            print yellow(local("docker ps -a", capture=True))
        else:
            print magenta("[Running process state]", bold=True)
            print yellow(local("docker ps", capture=True))

def rm():
    with hide('running'):
        for i in xrange(len(container)):
            print magenta('['+str(i+1)+'/'+str(len(container))+'] Clean up '+container_name[i]+'...', bold=True)
            print green(local('docker rm -f '+container_name[i], capture=True))

def test():
    up()
    ps('all')
    with hide('running'):
        print magenta('[info] Building source...', bold=True)
        print green(local('docker run --rm --volumes-from robocode-source --link rabbitmq:rabbitmq rf37535/build bash -c "cd /source && make"'))

        print magenta('[info] Running...', bold=True)
        print green(local('docker run --rm --volumes-from robocode-source --link rabbitmq:rabbitmq rf37535/build bash -c "cd /source && make run"'))

        print magenta('[info] Building source...', bold=True)
        print green(local('docker run --rm --volumes-from robocode-source --link rabbitmq:rabbitmq rf37535/build bash -c "cd /source && make clean"'))
    rm()

