# git-codecademy

* working Directory: where you'll be doing all the work: creating, editing, deleting and organizing files
* A Staging Area: where you'll list changes you make to the working directory
* A Repository: where Git permanently stores those changes as different versions of the project
____
* `git init` creates a new Git repository
* `git status` inspects the contents of the working directory and stging area
* `git add` adds files form theworking directory to the staging area
* `git diff` shows the difference between the working directory and the staging area
* `git commit' stores file changes form staging area in the repository
____

* `git log` shows a list of all prvious commits
* `git checkout HEAD filename` Discards changes in the working directory.
* `git reset HEAD filename` Unstages file changes in the staging area.
* `git reset SHA` Can be used to reset to a previous commit in your commit history.
____

* `git branch` Lists all a Git project's branches.
* `git branch branch_name` Creates a new branch.
* `git checkout branch_name` Used to switch from one branch to another.
* `git merge branch_name` Used to join file changes from one branch to another.
* `git branch -d branch_name` Deletes the branch specified.
* `git clone` Creates a local copy of a remote.
* `git remote -v` Lists a Git project's remotes.
* `git fetch` Fetches work from the remote into the local copy.
* `git merge origin/master` Merges origin/master into your local branch.
* `git push origin <branch_name>` Pushes a local branch to the origin remote.