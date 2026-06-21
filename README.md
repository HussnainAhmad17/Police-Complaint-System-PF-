# 👮 Police Complaint Management System (C++)

A secure, console-based management dashboard designed to efficiently log, track, and process public grievances. The system architecture enforces strict boundaries between public operations (submitting and tracking complaints) and privileged administrative tasks (updating status, generating system reports, and purging records).

## 🚀 Core Features

* **Role-Based Authentication:** Features a secure administrator portal requiring credentials (`admin` / `1234`) with a built-in brute-force restriction that locks the interface after 3 failed login attempts.
* **Persistent File I/O Stream:** Automatically handles flat-file synchronization (`complaints.txt`). It deserializes existing data at system startup and serializes new records during runtime to ensure data persistence across system restarts.
* **Robust Input Validation & Sanitization:** Implements specialized validation algorithms to strictly enforce:
  * 13-digit National Identity formatting (CNIC check)
  * 11-digit mobile/phone string structures
  * Strict calendar date formats (`DD/MM/YYYY`)
* **Relational Querying & Search:** Enables granular sequential lookups, allowing administrators to search complaints by unique alphanumeric Complaint IDs or complainant names.
* **Comprehensive Analytics & Reporting:** Generates structured institutional reports grouped dynamically by legal categories (e.g., Theft, Assault) or current lifecycle status (Pending, In Progress, Resolved).
* **Array-Based CRUD Lifecycle:** Efficiently manages data structures under a fixed global capacity constraint, utilizing index-shifting mechanics to safely execute record modifications and soft deletions.

## 🛠️ Concepts Learned & Applied

* File stream processing via `<fstream>` libraries (`ifstream` and `ofstream`).
* Advanced control of terminal alignment and tabular data reporting using `<iomanip>` (`setw`).
* Fail-safe I/O buffer management using `cin.clear()` and `cin.ignore()` to successfully intercept and neutralize illegal character flags or stream overflow attempts.
* Procedural software engineering and menu-driven command loops (`do-while` / `switch-case`).

## 💻 How to Run

### Prerequisites
Ensure you have a C++11 or newer compliant compiler installed (such as GCC/G++ or Clang).

### Execution Steps
1. Clone this repository:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/police-complaint-system-cpp.git](https://github.com/YOUR_USERNAME/police-complaint-system-cpp.git)
