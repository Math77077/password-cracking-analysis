import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def main():
    experiments = {
        "data/results_early.csv": "Early (aaazzzzz)",
        "data/results_split.csv": "Split (99bbccdd)",
        "data/results_complex.csv": "Complex (M4x9A1zK)"
    }

    all_data = []

    for filename, scenario_name in experiments.items():
        if not os.path.exists(filename):
            print(f"Warning: Data file '{filename}' is missing! Skipping this scenario.")
            continue

        df_slice = pd.read_csv(filename)
        df_slice["Scenario"] = scenario_name
        all_data.append(df_slice)

    if not all_data:
        print("Error: No experimental CSV files were loaded. Aborting pipeline.")
        return
    
    master_df = pd.concat(all_data, ignore_index=True)

    USE_PORTUGUESE = True
    output_dir = "plots"
    os.makedirs(output_dir, exist_ok=True)
    sns.set_theme(style="whitegrid", palette="muted")

    plt.figure(figsize=(10, 6))

    ax1 = sns.barplot(
        data=master_df,
        x="Scenario",
        y="AvgTime_ms",
        hue="Algorithm"
    )
    
    if USE_PORTUGUESE:
        plt.title("Perfil de Desempenho Computacional: Tempo Médio de Execução", fontsize=14, fontweight="bold", pad=15)
        plt.xlabel("Complexidade da Senha Alvo (Cenário)", fontsize=12, labelpad=10)
        plt.ylabel("Duração do Processamento na CPU (ms)", fontsize=12, labelpad=10)
        plt.legend(title="Estratégia de Paradigma", loc="upper right", title_fontsize=10, fontsize=9, labelspacing=0.4)
        lang_suffix = "pt"
    else:
        plt.title("Computational Performance Profile: Average Execution Time", fontsize=14, fontweight="bold", pad=15)
        plt.xlabel("Target Password Complexity (Scenario)", fontsize=12, labelpad=10)
        plt.ylabel("Core CPU Duration (ms)", fontsize=12, labelpad=10)
        plt.legend(title="Paradigm Strategy", loc="upper right", title_fontsize=10, fontsize=9, labelspacing=0.4)
        lang_suffix = "en"
    
    plt.tight_layout()

    for container in ax1.containers:
        ax1.bar_label(container, fmt='%.1f', padding=3, fontsize=8)

    plt.savefig(f"{output_dir}/runtime_comparison_{lang_suffix}.png", dpi=300)
    plt.close() 
    print(f"Successfully generated: plots/runtime_comparison_{lang_suffix}.png")

    plt.figure(figsize=(10, 6))
    
    ax2 = sns.barplot(
        data=master_df, 
        x="Scenario", 
        y="AvgOracleHits", 
        hue="Algorithm"
    )
    
    ax2.set_yscale("log")
    
    if USE_PORTUGUESE:
        plt.title("Análise de Carga de Verificação: Total de Consultas ao Oráculo", fontsize=14, fontweight="bold", pad=15)
        plt.xlabel("Complexidade da Senha Alvo (Cenário)", fontsize=12, labelpad=10)
        plt.ylabel("Contagem Total de Contatos com o Oráculo (Escala Log)", fontsize=12, labelpad=10)
        plt.legend(title="Estratégia de Paradigma", loc="upper right", title_fontsize=10, fontsize=9, labelspacing=0.4)
        lang_suffix = "pt"
    else:
        plt.title("Verification Weight Analysis: Total Oracle Queries", fontsize=14, fontweight="bold", pad=15)
        plt.xlabel("Target Password Complexity (Scenario)", fontsize=12, labelpad=10)
        plt.ylabel("Total Oracle Contacts Count (Log Scale)", fontsize=12, labelpad=10)
        plt.legend(title="Paradigm Strategy", loc="upper right", title_fontsize=10, fontsize=9, labelspacing=0.4)
        lang_suffix = "en"
    
    plt.tight_layout()

    for container in ax2.containers:
        ax2.bar_label(container, fmt='%.0f', padding=3, fontsize=8)

    plt.savefig(f"{output_dir}/oracle_hits_comparison_{lang_suffix}.png", dpi=300)
    plt.close()
    print(f"Successfully generated: plots/oracle_hits_comparison_{lang_suffix}.png")

if __name__ == "__main__":
    main()