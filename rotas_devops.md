
rota **/api/write_database_file** irá receber um arquivo no body e escrever no arquivo de banco dados seguindo o path 
headders:
    - path: string
    - root_password: string

body:
    - file: file


rota **/api/read_database_file** irá receber um arquivo no body e escrever no arquivo de banco dados seguindo o path 
headders:
    - path: string
    - root_password: string
body:
    - file: file

rota **/api/delete_database_file** irá receber um arquivo no body e escrever no arquivo de banco dados seguindo o path 
headders:
    - path: string
    - root_password: string

rota **api/list_database_files_recursively** irá listar todos os arquivos do banco de dados

headders:
    - path: string
    - root_password: string

body:
~~~json
[
    {"file":"path/to/file", "sha":"sha256"},
    {"file":"path/to/file", "sha":"sha256"},
    
]
~~~

implemente também as funcionalidades na cli:
start do servidor:
~~~bash
vibelog start --port 8080 --database_path /path/to/database
~~~
upload e sincronização do banco de dados:
~~~bash
vibelog upload --path /path/to/file --root_password your_password --url http://localhost:8080
~~~


