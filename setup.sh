#!/bin/sh

# Remove the remote (you probably want your own instead).
git remote remove origin

# Revert to first commit, add and commit everything as single commit.
git reset "$(git rev-list --max-parents=0 --abbrev-commit HEAD)"

git add --all

name=$(git config user.name)
email=$(git config user.email)

# If this script is called with an argument, use that as the amended author
# EX: ./setup.sh "Author Name <author_email@email.com>"
if [[ "$1" ]]; then
	git commit --amend --author="$1"
else
	git commit --amend --author="$name <$email>" 
fi
