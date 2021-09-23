#!/bin/sh

echo "release
develop
feature/
bugfix/
prerelease/
hotfix/
support/
"|git flow init -f $*