import pandas as pd
import matplotlib.pyplot as plt

# --- Part 1: convergence plot from the non-stiff exercise ---
df1 = pd.read_csv("errors.csv")
plt.figure()
plt.loglog(df1["h"], df1["error"], marker="o", label="Erreur (u'=2xu)")
plt.loglog(df1["h"], df1["h"], linestyle="--", label="Pente 1 (O(h))")
plt.xlabel("h"); plt.ylabel("Erreur")
plt.title("Convergence Euler explicite")
plt.legend(); plt.grid(True, which="both")
plt.savefig("convergence_nonraide.png")

# --- Part 2: error comparison on the stiff problem ---
df2 = pd.read_csv("errors_raide.csv")
plt.figure()
plt.loglog(df2["h"], df2["err_ex"], marker="o", label="Euler explicite")
plt.loglog(df2["h"], df2["err_im"], marker="s", label="Euler implicite")
plt.xlabel("h"); plt.ylabel("Erreur à x=2")
plt.title("Erreur - problème raide")
plt.legend(); plt.grid(True, which="both")
plt.savefig("convergence_raide.png")

# --- Part 3: trajectories showing instability ---
for fname, tag in [("traj_h01.csv", "h=0.1 (instable attendu)"),
                    ("traj_h001.csv", "h=0.01 (stable)")]:
    df = pd.read_csv(fname)
    plt.figure()
    plt.plot(df["x"], df["u_ex"], label="Euler explicite", marker=".")
    plt.plot(df["x"], df["u_im"], label="Euler implicite", marker=".")
    plt.plot(df["x"], df["u_exact"], label="Solution exacte", linestyle="--")
    plt.xlabel("x"); plt.ylabel("u(x)")
    plt.title(f"Trajectoires - {tag}")
    plt.legend(); plt.grid(True)
    plt.savefig(f"trajectory_{tag[:5]}.png")

plt.show()