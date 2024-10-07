

# CERT Alert System

## Overview

The CERT Alert System is a C++ application developed to automate the process of monitoring and reporting on security advisories from the CERT Bund RSS feed. This program was developed for Bankhaus Scheich Wertpapierspezialist AG to streamline the process of staying informed about potential security threats that could affect the software systems in use.

## Features

- **Automated RSS Feed Parsing**: Automatically fetches and parses the CERT Bund RSS feed for new security advisories.
- **Keyword Filtering**: Allows users to add, remove, and list keywords to filter relevant advisories.
- **Email Notifications**: Configurable email settings to send notifications when a relevant advisory is found.
- **Desktop Notifications**: Provides desktop notifications for new advisories.
- **Logging**: Logs all advisories to a specified log file to avoid duplicate alerts.
- **Auto-Run**: Configurable auto-run feature to periodically check for new advisories.

## Development Process

The development process involved:

1. **Requirements Gathering**: Understanding the needs of Bankhaus Scheich Wertpapierspezialist AG.
2. **Design**: Creating a robust design to ensure maintainability and scalability.
3. **Implementation**: Writing clean and modular code with a focus on C++ best practices.
4. **Testing**: Rigorous testing to ensure the application functions as expected under various conditions.
5. **Deployment**: Preparing the application for deployment on client systems.

## How to Use

### Prerequisites

- Ensure you have a C++ compiler installed.
- Install [SQLite3](https://www.sqlite.org/download.html).
- Install the necessary libraries (e.g., pugiXML).

### Installation

1. **Clone the Repository**
   ```sh
   git clone https://github.com/basel200de/CERT_Alert_System.git
   cd CERT_Alert_System
   ```

2. **Build the Project**
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

### Configuration

1. **Run the Program**
   ```sh
   ./CERT_Alert_System
   ```

2. **Menu Options**

   - **Configure Email Settings**: Enter your email settings to receive notifications.
   - **Configure RSS Link**: Set the RSS feed link (default: CERT Bund RSS).
   - **Configure Log File Path**: Specify the path for the log file.
   - **Configure Interval for Auto Run**: Set the interval for automatic RSS parsing.
   - **Add Keyword**: Add keywords to filter relevant advisories.
   - **Remove Keyword**: Remove keywords.
   - **List Keywords**: List all configured keywords.
   - **Parse RSS Feed**: Manually parse the RSS feed for advisories.
   - **Enable/Disable Auto Run**: Toggle the auto-run feature.
   - **Exit**: Exit the application.


## Acknowledgments

This program was developed by Basel M.G Hussein for Bankhaus Scheich Wertpapierspezialist AG.

