import csv

def checar_ordenacao_timestamp(caminho_csv, ordem_ascendente=True):
    """
    Verifica se o CSV está ordenado por timestamp.
    Se ordem_ascendente=True, exige timestamp_atual >= timestamp_anterior.
    Se ordem_ascendente=False, exige timestamp_atual <= timestamp_anterior.
    Interrompe após 10 erros de leitura ou 10 quebras de ordenação.
    """

    erros = []
    count_erros_leitura = 0
    count_nao_ordenado = 0

    with open(caminho_csv, 'r', newline='', buffering=1 << 20) as f:
        leitor = csv.reader(f)
        cabeçalho = next(leitor)
        idx_ts = cabeçalho.index("timestamp")

        # Inicializa com a primeira linha de dados
        primeira = next(leitor)
        ultimo_linha = 2  # já lemos cabeçalho (1) e primeira (2)
        ultimo_ts = int(primeira[idx_ts])

        for i, linha in enumerate(leitor, start=3):
            # Tentativa de leitura do timestamp
            try:
                ts = int(linha[idx_ts])
            except Exception as e:
                count_erros_leitura += 1
                print(f"❌ Erro de leitura na linha {i}: {e}")
                if count_erros_leitura > 10:
                    print("⚠️ Mais de 10 erros de leitura — interrompendo.")
                    break
                continue

            # Verifica ordenação
            if ordem_ascendente:
                fora = ts < ultimo_ts
                cmp = "<"
            else:
                fora = ts > ultimo_ts
                cmp = ">"

            if fora:
                count_nao_ordenado += 1
                erros.append((ultimo_linha, ultimo_ts, i, ts))
                print(
                    f"🚨 NÃO ORDENADO! "
                    f"Linha {i} (ts={ts}) {cmp} "
                    f"Linha {ultimo_linha} (ts={ultimo_ts})"
                )
                if count_nao_ordenado > 10:
                    print("⚠️ Mais de 10 quebras de ordenação — interrompendo.")
                    break
                # não atualiza ultimo_ts/número de linha
            else:
                # tudo certo, atualiza o "último válido"
                ultimo_ts = ts
                ultimo_linha = i

            # feedback de progresso
            if i % 1_000_000 == 0:
                print(f"✔️ {i} linhas verificadas...")

    # Resumo final
    if erros:
        print(f"\n❌ Total de {len(erros)} quebras encontradas.")
    else:
        print("\n✅ Todas as linhas estão corretamente ordenadas por timestamp.")

# Exemplo de uso:
path = "C:/Users/Usuario/Desktop/Quicksort/julia/sorted_LinkedSta_1000000_2025-06-17_22-31-49.csv"
checar_ordenacao_timestamp(path)
