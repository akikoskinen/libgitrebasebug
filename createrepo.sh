#!/bin/bash

REPODIR="testrepo"

cd `dirname $0`

rm -rf $REPODIR
mkdir $REPODIR
cd $REPODIR

git init

touch README
git add README
git commit -m "Initial commit"

echo 1 > problem.txt
chmod 644 problem.txt
git add problem.txt
git commit -m "Added problem.txt"

git checkout -b other
echo other > other.txt
git add other.txt
git commit -m "Added other.txt"

git checkout master
echo 2 > problem.txt
chmod 755 problem.txt
git add problem.txt
git commit -m "Modified content and permissions"
