# define data strucuture -> arrays, matrixes, linked lists or vector

# define theme of the game

# bonus or not
- minimap
- wall collision

# TODO
- docs

# DONE
- ft_vector full version
- create github -> 2 different branches

# PARSER

# pre-exec

## arg validations
### BACKLOG
- treat file called ".cub"?
### TODO
- treat errors like: "Error\n" followed by an explicit error message
### DOING
- INIT EVERYTHING
### DONE
- is empty
- is not a folder
- number of args
- right extension(.cub) 
- exists

# .cub validations

## elements
### BACKLOG
### TODO
- treat errors like: "Error\n" followed by an explicit error message
- MUST EXIT AFTER AN ERROR
- CLEAN LEAKS ON EXIT
- CHECK UNUSED FUNCTIONS, VARS, STRUCTS, ETC
- INVALID CHAR LEAK
- norm
- use takeo's makefile
- TRATAR O FREE EM CASO DE NENHUM PLAYER
### DOING
- throw all relevant elements on a struct
- INIT EVERYTHING
### DONE
- dont accept elements after the map
- careful with \n and empty lines
- treat spaces and tabs
- make separate counter
- last line empty 
- textures cardinal points cannot be missing
- floor and ceiling colors line cannot be missing
- textures cardinal points cannot repeat
- floor and ceiling colors line cannot repeat
- 4294967297 overflow
- where elements end
- RBG of the floor and celiing colors
- receive elements in any order
- textures are valid (exists, right extension, etc)
- where the map starts?
- check how to read the first lines that define textures and etc
- read textures and rgb in any order
- signals on rgb
- zeros on rgb
- spaces on rgb

## map
### BACKLOG
- two maps on the same file?
- accept triangles?
### TODO
- throw all relevant information on a struct
- where it ends
- make sure texture are on the right cardinal point
- make sure the player is looking for the right cardinal point
- treat errors like: "Error\n" followed by an explicit error message
### DOING
- INIT EVERYTHING
- must be surrounded by walls
- treat non ascii chars
- floodfill
- make sure floodfill starts on NEWS or not
- make sure to treat only NEWS01(inside the map) 'spaces' and 'tabs'(outside)
- consider iterative flood_fill
### DONE
- treat tab as 1 width
- holes in the map
- NWSE cannot repeat
- empty line in the middle of the map
- where the map starts
- send data to validation
- get height
- get width

