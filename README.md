# Multiparadigm Password Cracker: Algorithmic Performance Benchmarking

An advanced computer science engineering exploration evaluating the structural trade-offs between four distinct algorithmic design paradigms applied to a high-complexity cryptographic search space. This project benchmarks execution metrics across varying password target boundaries and exports high-fidelity figures tailored for an official SBC (Sociedade Brasileira de Computação) technical publication format.

---

## Algorithmic Paradigms Implemented

This system solves an 8-character alphanumeric search space ($62^8 \approx 218.3$ trillion combinations) using four distinct architectural methodologies:

1. **Exhaustive Brute Force ($O(k^n)$):** Evaluates combinations sequentially utilizing a base-$k$ counter. Acts as our control baseline for worst-case execution performance.
2. **Divide and Conquer ($O(k^{n/2})$):** Bi-sects the 8-character string problem into two independent, symmetric 4-character subproblems, reducing the mathematical search space down to dual $62^4$ domains.
3. **Dynamic Programming ($O(k^{n/2})$):** Extends the prefix-splitting logic by caching discovered components inside a memoization look-up table to prevent redundant operational recalculations.
4. **Genetic Algorithm (Heuristic Search):** Treats individual password candidates as 8-gene chromosomes within an evolving population, utilizing a fitness function feedback oracle to guide selection, crossover, and mutation vectors.

---

## Repository Architecture & Engineering Design

```text
password_cracker/
├── data/                       # Tracked empirical benchmark metrics (CSV)
│   ├── results_early.csv       # Baseline target: 'aaazzzzz'
│   ├── results_split.csv       # Prefix symmetry target: '99bbccdd'
│   └── results_complex.csv     # Scrambled alphanumeric target: 'M4x9A1zK'
├── plots/                      # High-resolution publication figures (.png)
│   ├── oracle_hits_comparison_en.png
│   └── runtime_comparison_en.png
├── src/                        # Core C implementation modules
│   ├── brute_force.c
│   ├── genetic.c
│   ├── oracle.c                # Encapsulated static secret memory oracle API
│   └── oracle.h
├── tests/
│   └── my_secret.txt           # Active evaluation runtime target
├── Makefile                    # Compiles native optimized executable 'cracker'
├── main.c                      # CLI parsing and performance timing harness
├── analysis.py                 # Automated multi-file visualization pipeline
├── password-cracker-report.pdf # Final compiled SBC experimental technical report
└── requirements.txt            # Isolated environment dependency map

```

### Why we designed it this way:

* **The Simulated Oracle Design (`oracle.c`):** In a real-world production system, authentication networks rely on one-way cryptographic hash functions (e.g., bcrypt, SHA-256) that offer absolutely no partial feedback—returning strictly a binary pass/fail state. The partial validation pathways (`check_partial`, `get_fitness`) implemented here serve as an **experimental simulation tool**. This abstraction allows us to model how advanced cryptographic vulnerabilities—such as side-channel leakage—behave under different algorithmic paradigms, providing a safe sandbox to analyze search-space optimizations.
* **Environment Sandboxing (`venv`):** Python dependencies are strictly confined within a virtual environment layer. This guarantees absolute machine portability and shields the host Pop!_OS system files from package-version conflicts.
* **Dynamic Ingestion Data Pipeline (`analysis.py`):** Rather than handling messy global dependencies or manual spreadsheet data entry, the Python layer dynamically sweeps the `data/` directory, isolates scenario parameters, normalizes missing fields caused by Brute Force timeouts, and automatically renders multi-grouped bar graphics.

---

## Experimental Metrics Overview

### 1. Computational Performance Profile (Linear Scale)

* **Brute Force Bottleneck:** Standard sequential iteration handles early search spaces but quickly encounters exponential execution ceilings on more complex prefixes, resulting in real-world application hang/timeouts.
* **Divide & Conquer vs. Dynamic Programming Overhead:** While both strategies drastically optimize search spaces compared to brute-forcing, D&C exhibits lower execution times than DP. This proves that for single-password analytical runs, the memory allocation and lookup overhead of a memoization structure costs more than it saves.
* **Genetic Superiority:** Bypasses sequential traversal entirely, mutating toward solutions in fractions of a single millisecond ($<0.6\text{ ms}$).

### 2. Verification Weight Analysis (Logarithmic Scale)

* By mapping total oracle queries to a base-10 logarithmic scale ($\log_{10}$), we expose the massive mathematical chasm between strategies. The Genetic Algorithm resolves complex targets with a mere $\sim 4,300$ oracle queries, contrasting sharply against the $15.6\text{ million}$ queries required by prefix algorithms and the $375.4\text{ million}$ checks consumed by an early brute-force run.

---

## SBC Technical Report Status

* **Status:** `Completed` 
* **Format:** SBC Conference Template (Sociedade Brasileira de Computação).
* **Language:** Portuguese (with English Abstract).
* **Delivery Artifact:** [Download PDF Report](./password-cracker-report.pdf) 
* **Core Focus:** Evaluates empirical trade-offs, CPU runtimes, and oracle hits across 13 controlled executions. Discusses side-channel fitness mapping (timing/power analysis equivalents), dynamic programming memoization overheads, and firewall viability constraints under restrictive 5-attempt IP-lockout conditions.
* **Academic Integrity:** Transparently documented AI-assisted linguistic and styling revisions in accordance with CNPq Portaria nº 2.664/2026 guidelines.

---

## Installation & Replication Guide

Follow these steps sequentially to configure the isolated environment, compile the native optimized C executable, execute the benchmark matrices, and reproduce the analytical graphics.

### 1. Prerequisites
Ensure your system possesses standard development utilities (`gcc` and `make`) alongside Python 3:
```bash
# On Pop!_OS / Ubuntu / Debian systems:
sudo apt update
sudo apt install build-essential python3 python3-venv python3-pip

```

### 2. Sandbox Setup & Python Dependencies

Initialize the isolated virtual environment context layer and deploy the required visualization libraries:

```bash
# Initialize the virtual environment container boundary
python3 -m venv venv

# Activate the sandbox context layer
source venv/bin/activate

# Upgrade pip and install the precise locked dependency manifest
pip install --upgrade pip
pip install -r requirements.txt

```

*(Note: Your terminal prompt will display a `(venv)` prefix confirming global OS directory decoupling).*

### 3. Compile the High-Performance C Engine

Utilize the pre-configured automation script to invoke `gcc` with standard high-optimization flags:

```bash
# Compile and output the native binary 'cracker'
make

# Optional: Wipe intermediate compilation objects (.o) if rebuilding
make clean

```

### 4. Execute the Experimental Benchmarks

To simulate and replicate the multi-scenario empirical dataset, manually deploy a target password inside the tracked text module and invoke the orchestrator harness:

```bash
# Create or modify the evaluation password target
echo "M4x9A1zK" > tests/my_secret.txt

# Run a chosen strategy to append its parameters directly to results.csv
./cracker --algo genetic --mode file --path tests/my_secret.txt

```

*(Remember to move your `results.csv` files into the `data/` directory named as `results_early.csv`, `results_split.csv`, or `results_complex.csv` to partition your scenarios safely).*

### 5. Execute the Automated Data Pipeline

With the `venv` still active and raw datasets safely mapped inside the `data/` layout, fire up the data parsing pipeline:

```bash
python analysis.py

```

Check the freshly generated `plots/` directory tree to review your high-resolution, publication-ready `.png` asset canvases!
