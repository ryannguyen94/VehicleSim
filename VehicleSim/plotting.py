import csv
from plotly.subplots import make_subplots
import plotly.graph_objects as go
import numpy as np

data = {}
header = []
row_cnt = 0
with open("log.csv", mode="r") as file:
    csv_file = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    for i, lines in enumerate(csv_file):
        if i == 0:
            header = lines
            for j in range(len(lines)):
                data[lines[j]] = []
        else:
            row_cnt += 1
            for j in range(len(lines)):
                data[header[j]].append(lines[j])

number_of_subplots = len(header)
fig = make_subplots(rows=number_of_subplots, cols=1, shared_xaxes=True, vertical_spacing=0.01,
                    subplot_titles=tuple(header))

dt = 0.01
t_array = np.linspace(0, dt*(row_cnt - 1), row_cnt)
for i in range(len(header)):
    fig.add_trace(go.Scatter(x=t_array, y=data[header[i]], name=header[i]), row=i+1, col=1)

# fig.update_yaxes(title_text="kph", row=1, col=1)
fig.update_xaxes(showspikes=True, spikecolor="green", spikesnap="cursor", spikemode="across")
fig.update_layout(height=number_of_subplots * 400, spikedistance=1000, hoverdistance=100, hovermode='x')
fig.show()

fig1 = make_subplots(rows=1, cols=1, shared_xaxes=True, vertical_spacing=0.01,
                    subplot_titles=tuple(header))
fig1.add_trace(go.Scatter(x=data["x"], y=data["y"], name="pos"), row=1, col=1)
# fig1.update_yaxes(title_text="kph", row=1, col=1)
fig1.update_xaxes(showspikes=True, spikecolor="green", spikesnap="cursor", spikemode="across")
fig1.update_layout(spikedistance=1000, hoverdistance=100, hovermode='x')
fig1.show()

# fig.write_html("attidude_dll_plot_20201221.html")