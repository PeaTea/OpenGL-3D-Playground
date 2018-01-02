# IF YOU WANT TO USE THE PROVIDED .vcx* FILES, FOLLOW THE STEPS BELOW

You need 3 directories:
    GLEW
    glm
    SFML

Each folder contains a include and a lib directory (in case of glm it's just include), containing the 
same-named directories of the downloaded dependencies, so in case of GLEW, it would be like this:

    GLEW - include - GL - [include_files]
    GLEW - lib - Release - Win32 - [lib_files]
                         - x64 - [lib_files]
