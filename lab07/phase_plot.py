import matplotlib.pyplot as plt

def phase_plot():
    colors = ['b', 'g', 'r', 'c', 'm']
    labels = ['(1.0, 0.4)', '(1.0, 0.6)', '(1.0, 0.8)', '(-1.0, 0.6)', '(-1.0, 0.4)']

    for i in range(1, 6):
        filename = f"output{i}.data"
        data = []
        with open(filename, 'r') as file:
            for line in file:
                u, v = map(float, line.split())
                data.append((u, v))

        u_values, v_values = zip(*data)
        plt.plot(u_values, v_values, label=labels[i-1], color=colors[i-1])

    plt.xlabel('u')
    plt.ylabel('v')
    plt.title('Phase Plot')
    plt.legend()
    plt.savefig("phase_plot.png")

if __name__ == "__main__":
    phase_plot()

