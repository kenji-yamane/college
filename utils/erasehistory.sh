#!/bin/bash

read -p "Are you sure? " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
    exit 1
fi

PRINCIPAL_BRANCH_NAME=main
ALL_BRANCHES=$(git branch -a)
NOT_MAIN_BRANCHES=$(echo "$ALL_BRANCHES" | grep -v \\* | grep -v origin/$PRINCIPAL_BRANCH_NAME\$)
BASENAMES=$(echo "$NOT_MAIN_BRANCHES" | grep '^  remotes/origin/')
TO_DELETE_BRANCHES=$(echo "$BASENAMES" | sed 's=^  remotes/origin/==')
git push origin --delete $(echo $TO_DELETE_BRANCHES)

FIRST_COMMIT=$(git rev-list --max-parents=0 HEAD | tail -n 1)
git reset --soft $FIRST_COMMIT
git add --all
git commit -m "squashed history"
git push -f

