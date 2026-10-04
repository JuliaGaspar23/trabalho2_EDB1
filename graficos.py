import pandas as pd
import matplotlib.pyplot as plt
import os

algoritmos = ['insertion', 'selection', 'bubble', 'merge', 'quick']
nomes = {
    'insertion': 'Insertion Sort',
    'selection': 'Selection Sort',
    'bubble': 'Bubble Sort',
    'merge': 'Merge Sort',
    'quick': 'Quick Sort'
}

def ler_csv(caminho):
    for enc in ['utf-8', 'utf-16', 'latin1']:
        for sep in [',', ';', '\t']:
            try:
                df = pd.read_csv(caminho, encoding=enc, sep=sep)
                if df.shape[1] >= 2 and len(df) > 0:
                    return df
            except Exception:
                continue
    return None

def gerar_grafico(cenario, titulo, nome_arquivo):
    plt.figure(figsize=(10, 6))
    curvas_desenhadas = 0
    
    for alg in algoritmos:
        arquivo = f"{cenario}_caso_{alg}.csv"
        if os.path.exists(arquivo):
            df = ler_csv(arquivo)
            if df is not None:
                df.columns = [str(c).replace('\x00', '').strip() for c in df.columns]
                x = pd.to_numeric(df.iloc[:, 0].astype(str).str.replace('\x00', ''), errors='coerce')
                y = pd.to_numeric(df.iloc[:, 1].astype(str).str.replace('\x00', ''), errors='coerce')
                
                # Converte nanosegundos para milissegundos
                y_ms = y / 1e6 
                
                mask = x.notna() & y_ms.notna()
                if mask.sum() > 0:
                    plt.plot(x[mask], y_ms[mask], label=nomes[alg], linewidth=2)
                    curvas_desenhadas += 1

    plt.title(titulo, fontsize=13, fontweight='bold')
    plt.xlabel('Tamanho do Vetor (N)', fontsize=11)
    plt.ylabel('Tempo (Milissegundos)', fontsize=11)
    plt.grid(True, linestyle='--', alpha=0.6)
    if curvas_desenhadas > 0:
        plt.legend(loc='upper left', fontsize=10)
    plt.tight_layout()
    plt.savefig(nome_arquivo, dpi=300)
    plt.close()
    print(f"Imagem '{nome_arquivo}' gerada com {curvas_desenhadas} curvas.")

# Gerar os dois gráficos
gerar_grafico('pior', 'Comparação dos Algoritmos de Ordenação - Pior Caso', 'grafico_pior_caso.png')
gerar_grafico('melhor', 'Comparação dos Algoritmos de Ordenação - Melhor Caso', 'grafico_melhor_caso.png')