Autora: Larissa de Souza Bastos

# Lista de arquivos: 
    (arquivos que usei para testes):
    pequeno.bin
    padrao.bin
    grande.bin

# Dificuldades enfrentadas
    - Manipulação de arquivos binários: por ser minha primeira vez trabalhando com isso, tive dificuldade em compreender a leitura e escrita binária com fread e fwrite, especialmente o uso correto de offsets (fseek) para acessar diferentes partes do arquivo (superbloco, dados e diretório).

    - Controle do offset do diretório: tive dificuldade em controlar a área de diretório e seu offset devido as mudanças que aconteciam após as inserções.

    - Uso de malloc e realloc: como manipulação de arquivos é algo novo para mim, tive duvidas de como trabalhar corretamente com malloc e realloc.

    - Foi necessário a alteração do cabeçalho de algumas funções para seu funcionamento, todas feitas de acordo com o professor. A função gbv_ordena não foi feita, com a permissão do professor

    - As funções gbv_add e gbv_view foram as mais difíceis na minha opinião, por trabalharem muito com acesso a arquivos.

# Bugs conhecidos
    Não sei se são exatamente bugs, mas para deixar explícito:
    - Arquivos binários são exibidos diretamente no terminal, podendo resultar em saída não legível.
    - O programa pode falhar se o arquivo .gbv estiver previamente corrompido, sendo necessário removê-lo e recriá-lo.
    - A remoção remove apenas os metadados, podendo deixar lixo de memória no arquivo .gbv.
