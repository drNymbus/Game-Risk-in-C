# Game-Risk-in-C
## Description
The classic Risk game with an ASCII display in terminal.
This game allows you to play Risk, with some friends, on your terminal, with a simple interface.

You can also create your own custom Risk. This is an easy but really long way to create
a all new board game. You just need to follow the same schema than the files "country.txt" and "continent.txt".
The scheme:

<ul>
  for country.txt
    <ul>--> country_id country_name country_x country_y country_nb_conn list_country_id</ul>
  for continent.txt
    <ul>--> continent_name nb_country</ul>
    <ul>--> list_country_id</ul>
</ul>

**Files**
    <ul>
    model.c
        <ul>--> Contains all structures that contain game data.</ul>
        <ul>--> Some functions are in this files to factorise some code. </ul>
        <ul>--> Since i'm alone on this porject i choose to manipulate my data structures directly.</ul>
    initializer.c
        <ul>--> Contains all the reader input from the initializer folder.</ul>
        <ul>--> From country.txt, fill structs necessary for the game to be played.</ul>
        <ul>--> Same for continent.txt.</ul>
    view.c
        <ul>--> Contains all prints to display a user interface.</ul>
    interact.c
        <ul>--> Contains all functions to read user command input.</ul>
        <ul>--> Contains also some functions o manipulate strings.</ul>
    main.c
        <ul>--> Contains the logic of the game.</ul>
        <ul>--> With no surprise this file contains the main function.</ul>
    </ul>

## Future
<ol>Some     bots will be added in the game to fill a game or to play alone.</ol>
<ol>A windowed mode with a Graphical Interface will be developped later.</ol>
<ol>A multiplayer mode can ba added.</ol>
<ol>Ultimate goal : redo all code in C++</ol>