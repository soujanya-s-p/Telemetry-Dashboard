# Real-Time Telemetry Dashboard & Network Utility

A desktop application in **C++/Qt** for visualizing live vehicle telemetry data, logging it, and exporting for post-mission analysis.  

It supports real-time updates, efficient UI handling using **Qt Signals & Slots**, CSV logging, and XML export.

---

## Features

- **Live Visualization:**  
  - Real-time plotting of vehicle **altitude**.
  - Dynamic display of **voltage** and coordinates (latitude, longitude).
- **Data Handling:**  
  - Logs telemetry to **CSV** for post-mission analysis.
  - **Export to XML** as a black-box log.
- **Optimized UI:**  
  - Smooth updates using Qt **Signals & Slots**.
  - Handles high-speed data bursts without freezing.

---

## Tech Stack

- **C++** and **Qt 6** (Widgets & QtCharts)  
- **Qt Signals & Slots** for asynchronous updates  
- CSV & XML file handling for logging and export  

Optional future extensions:  
- **Python (Pandas, Streamlit, Plotly, Scikit-learn)** for advanced post-mission analysis

---

## Setup Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/TelemetryDashboard.git
   cd TelemetryDashboard

Open in Qt Creator:
Open TelemetryDashboard.pro or the .pro project file.

Build and Run:

Configure for your compiler (e.g., MinGW or MSVC).

Build → Run.

Using the App:

Connect your telemetry simulator or real device to port 5000.

Watch live charts and labels update.

CSV is automatically logged to telemetry_log.csv.

Export XML via the Export button.

File Structure
TelemetryDashboard/
│
├─ main.cpp
├─ mainwindow.h
├─ mainwindow.cpp
├─ dataparser.h/.cpp
├─ telemetryserver.h/.cpp
├─ telemetry_dashboard.pro
└─ resources/ (optional icons, UI resources)
Usage Example

Start the Telemetry Simulator.

Run the Dashboard.

Observe live telemetry.

Click Export XML to save the session.

License

MIT License. Free to use, modify, and distribute.


---

# 🟢 GitHub Push Steps

1. **Initialize Git in your project folder** (if not already):
```bash
git init

Add all files:

git add .

Commit:

git commit -m "Initial commit: Real-Time Telemetry Dashboard C++/Qt"

Create a repo on GitHub (e.g., TelemetryDashboard)

Add GitHub remote:

git remote add origin https://github.com/yourusername/TelemetryDashboard.git

Push to GitHub:

git branch -M main
git push -u origin main