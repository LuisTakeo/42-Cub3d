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
- is empty
- is not a folder
- treat errors like: "Error\n" followed by an explicit error message
### DONE
- number of args
- right extension(.cub) 
- exists

# .cub validations

## elements
### TODO
- where elements end?
- textures cant be duplicates
- treat spaces on texture filenames
- accept spacing on elements spacing
- treat spaces and tabs
- careful with \n and empty lines
- "Error\n" followed by an explicit error message
- dont accept elements after the map
- 4294967297 overflow
- treat errors like: "Error\n" followed by an explicit error message
### DONE
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
- where the map starts?
- treat tab as 4 width?
- where it ends
- floodfill
- empty line in the middle of the map
- must be surrounded by walls
- make sure texture are on the right cardinal point
- make sure the player is looking for the right cardinal point
- make sure floodfill starts on NSWE
- make sure to treat only NSWE01(inside the map) 'spaces' and 'tabs'(outside)
- treat non ascii chars
- two maps on the same file?
- treat errors like: "Error\n" followed by an explicit error message
- accept triangles?
### DONE
- send data to validation
- get height
- get width
