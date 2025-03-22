import numpy as np # type: ignore
import matplotlib.pyplot as plt # type: ignore
from scipy.optimize import curve_fit # type: ignore
import data

bunnies, does, kits = data.bunnies, data.does, data.kits
months = np.arange(0, len(bunnies))

total_population = bunnies + does + kits

def compute_growth_rate(data):
    return np.concatenate(([0], np.diff(data) / data[:-1]))

growth_bunnies = compute_growth_rate(bunnies)
growth_does = compute_growth_rate(does)
growth_kits = compute_growth_rate(kits)
growth_total = compute_growth_rate(total_population)

def exponential_growth(x, P0, r):
    return P0 * np.exp(r * x)

params_total, _ = curve_fit(exponential_growth, months, total_population, p0=[4, 0.01])
P0_total, r_total = params_total

prop_bunnies = bunnies / total_population * 100
prop_does = does / total_population * 100
prop_kits = kits / total_population * 100

plt.figure(figsize=(16, 8))

plt.subplot(2, 2, 1)
plt.plot(months, total_population, label="Observed Total Population", marker='o')
plt.plot(months, exponential_growth(months, P0_total, r_total), label=f"Exponential Fit (r={r_total:.3f})", linestyle='--')
plt.xlabel("Months")
plt.ylabel("Population")
plt.title("Total Population and Exponential Growth Model")
plt.legend()

# plt.subplot(2, 2, 2)
# plt.plot(months, growth_bunnies, label="Bunnies Growth Rate", marker='.')
# plt.plot(months, growth_does, label="Does Growth Rate", marker='.')
# plt.plot(months, growth_kits, label="Kits Growth Rate", marker='.')
# plt.plot(months, growth_total, label="Total Growth Rate", linestyle='--')
# plt.xlabel("Months")
# plt.ylabel("Growth Rate")
# plt.title("Growth Rates Over Time")
# plt.legend()

plt.subplot(2, 2, 2)
data1 = data.age
normalized_data = [x / sum(data1) for x in data1]
plt.bar(np.arange(len(normalized_data)), normalized_data, edgecolor="black", color="teal")
plt.yscale("log")
plt.xlabel("Months")
plt.ylabel("Percentage (Log Scale)")
plt.title("Normalized Age Over Sequence of Months")

plt.subplot(2, 2, 3)
plt.stackplot(months, prop_bunnies, prop_does, prop_kits, labels=["Bunnies", "Does", "Kits"], alpha=0.7)
plt.xlabel("Months")
plt.ylabel("Percentage Contribution")
plt.title("Proportional Contributions to Total Population")
plt.legend(loc="upper left")

plt.subplot(2, 2, 4)
data1 = data.unnormalized_deaths
normalized_data = [x / sum(data1) for x in data1]
plt.bar(np.arange(len(normalized_data)), normalized_data, edgecolor="black", color="teal")
plt.yscale("log")
plt.xlabel("Months")
plt.ylabel("Percentage (Log Scale)")
plt.title("Normalized Data Over Sequence of Months (Logarithmic Scale)")

plt.tight_layout()
plt.show()
