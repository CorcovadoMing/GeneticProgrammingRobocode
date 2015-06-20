from __future__ import with_statement
from fabric.api import local
from fabric.colors import green, magenta, yellow
from fabric.context_managers import hide

def up():
    with hide('running'):
        print magenta("[1/2] Start up rabbitmq...", bold=True)
        print green(local("docker run -d --name rabbitmq rf37535/rabbitmq", capture=True))

        print magenta("[2/2] Start up robocode control engine...", bold=True)
        print green(local("docker run -d --name controlengine --link rabbitmq:rabbitmq rf37535/robocode:controlengine", capture=True))

def ps():
    with hide('running'):
        print magenta("[Process state]", bold=True)
        print green(local("docker ps -a", capture=True))

def rm():
    with hide('running'):
        print magenta("[1/2] Remove rabbitmq...", bold=True)
        print green(local("docker rm -f rabbitmq", capture=True))

        print magenta("[2/2] Remove rabbitmq...", bold=True)
        print green(local("docker rm -f controlengine", capture=True))