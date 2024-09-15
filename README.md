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
### TODO
- treat file called ".cub"?
- treat errors like: "Error\n" followed by an explicit error message
### DOING
- is empty
- is not a folder
### DONE
- number of args
- right extension(.cub) 
- exists

# .cub validations

## elements
### TODO
- careful with \n and empty lines
- "Error\n" followed by an explicit error message
- dont accept elements after the map
- 4294967297 overflow
- treat errors like: "Error\n" followed by an explicit error message
### DOING
- throw all relevant elements on a struct
- textures cardinal points cannot repeat
- floor and ceiling colors line cannot repeat
- textures cardinal points cannot be missing
- floor and ceiling colors line cannot be missing
- treat spaces and tabs
### DONE
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
### TODO
- throw all relevant information on a struct
- where it ends
- NWSE cannot repeat
- empty line in the middle of the map
- make sure texture are on the right cardinal point
- make sure the player is looking for the right cardinal point
- make sure to treat only NSWE01(inside the map) 'spaces' and 'tabs'(outside)
- treat non ascii chars
- two maps on the same file?
- treat errors like: "Error\n" followed by an explicit error message
- accept triangles?
- wholes in the map
### DOING
- must be surrounded by walls
- floodfill
- make sure floodfill starts on NSWE or not
- consider iterative flood_fill
### DONE
- treat tab as 1 width
- where the map starts
- send data to validation
- get height
- get width
