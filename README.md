##ArduinoGitNotifier
====================


####Git Hooks
=============
echo "\n" 
RepoName=$(git remote -v | head -n1 | awk '{print $2}' | sed 's/.*\///' | sed 's/\.git//')
Branch=$(git rev-parse --abbrev-ref HEAD)
# CommitHash=$(git log -n 1 --pretty=format:"%H")
# Author=$(git show $CommitHash --format="The author of %h was %an")

curl -X POST -d "repoName=$RepoName&branch=$Branch" http://localhost:8000
echo "\n"