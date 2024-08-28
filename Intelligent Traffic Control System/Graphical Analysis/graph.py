import matplotlib.pyplot as plt
import pandas as pd

# Data for the number of vehicles over time
breakpoints = [30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 360, 390, 420, 450, 480, 510, 540, 570, 600]
traditional_vehicles = [20, 37, 41, 43, 53, 52, 50, 50, 59, 59, 59, 53, 50, 48, 46, 42, 41, 51, 52, 54]
adaptive_vehicles = [21, 35, 30, 40, 42, 41, 40, 42, 45, 45, 50, 49, 48, 50, 50, 50, 48, 47, 46, 45]

# Data for occupancy rates
data = {
    'Traditional Occupancy': [2.133] * 20,
    'Adaptive Occupancy': [0, 2.47, 1.64, 0.82, 0.82, 2.47, 0.82, 1.64, 0.82, 1.64, 2.47, 0.82, 1.64, 0.82, 2.47, 0.82, 1.64, 0.82, 2.47, 0.82]
}
df = pd.DataFrame(data)
avg_occupancy = df.mean()

# Create a line graph for the number of vehicles
plt.figure(figsize=(10, 6))
plt.plot(breakpoints, traditional_vehicles, label='Traditional Vehicles', marker='o')
plt.plot(breakpoints, adaptive_vehicles, label='Adaptive Vehicles', marker='o',)
plt.title('Number of Vehicles Over Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Number of Vehicles')
plt.legend()
plt.grid(True)
plt.savefig('vehicles_over_time.png')
plt.show()

# Create a bar chart for the average occupancy rates
plt.figure(figsize=(8, 6))
avg_occupancy.plot(kind='bar', color=['blue', 'green'])
plt.title('Average Occupancy Rates')
plt.ylabel('Occupancy Rate')
plt.xticks(rotation=0)
plt.grid(axis='y')
plt.savefig('average_occupancy_rates.png')
plt.show()

# Create a pie chart for the reduction in traffic
total_vehicles_traditional = sum(traditional_vehicles)
total_vehicles_adaptive = sum(adaptive_vehicles)
reduction = total_vehicles_traditional - total_vehicles_adaptive
percent_reduction = (reduction / total_vehicles_traditional) * 100

plt.figure(figsize=(8, 6))
plt.pie([percent_reduction, 100 - percent_reduction], labels=['Reduction in Vehicles', 'Remaining Vehicles'], autopct='%1.1f%%', startangle=140, colors=['red', 'lightgrey'])
plt.title('Reduction in Traffic')
plt.savefig('traffic_reduction.png')
plt.show()
