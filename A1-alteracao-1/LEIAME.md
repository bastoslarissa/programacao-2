Autora: Larissa de Souza Bastos

# Alteração - A2: Chave de Acesso (Shift 4B)
    A solução que pensei foi inserir a chave de 4 bytes no início da biblioteca na função gbv_create e as outras funções deveriam ler essa chave com fread. Algo que deveria ser simples. Entretanto surgiu um erro: na primeira vez que roda o programa ela funciona, mas nas vezes seguintes, dá erro. Não consegui resolver. Fiz alguns testes, mas não consgui chegar em uma solução.