**Note**: This only applies on Windows.

The files in this folder are commands which can be used as long as the workspace settings of this repository apply (VSCode custom environment).
This folder has been added to the start of the path, which means that the files defined here have priority over any commands with the same name.
This serves the purpose of being able to use the docker image as an executable cross-compiler by simply writing `make all`, for example.
Similarily, other commands have been made available.

## Overview of available commands
`flash` - Loads the .rxe file corresponding to the first argument onto 
