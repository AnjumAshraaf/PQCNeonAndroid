# Post-Quantum Cryptography Benchmarking on Android

This repository contains Android applications developed for benchmarking **post-quantum cryptographic algorithms** — specifically, **NTRU** (three variants) and **Kyber** (parameterized). All algorithms are implemented in C and optimized using **ARM NEON** instructions for improved performance on mobile devices.

## 📱 Tested Device

* **Device**: Google Pixel 2
* **OS**: Android 8.0 (Oreo)
* **Processor**: Octa-core (4x2.35 GHz)
* **RAM**: 4 GB
* **API Level**: 28

## 🧩 Technologies Used

* **Languages**: C, Java
* **Native Interface**: Android NDK with JNI
* **Build System**: CMake
* **NEON Optimizations**: ARM NEON C Library
* **IDE**: Android Studio

---

## 🔐 NTRU Applications

Three separate Android applications have been developed — one for each variant of the **NTRU** algorithm.

* Each app integrates the **C implementation** of its respective NTRU variant.
* Algorithms are **NEON-optimized** to improve performance on ARM processors.
* JNI is used to invoke native C functions from the Android application layer.

---

## 🔐 Kyber Application

A **single Android application** is developed for all **Kyber variants**:

* Users can select parameter **K = 2, 3, or 4** in params.h to evaluate the performance of:

  * `Kyber512`
  * `Kyber768`
  * `Kyber1024`
* Internally, this controls the key encapsulation mechanism parameters at runtime.

---

## 🚀 Running the Applications

1. **Clone this repository** into your local machine.
2. **Open each app folder** separately in **Android Studio**.
3. **Wait for Gradle** to download dependencies and sync the project.
4. **Run the application** on a real device (e.g., Pixel 2) using USB debugging.
5. Open **Logcat** and look for logs with the respective **tag** to view performance outputs.

---

## 📂 Folder Structure

---

## 📋 Notes

* This project is designed to **benchmark post-quantum algorithms** under real Android environments.
* Make sure to run these apps on **physical devices** (not emulators) for accurate performance results.
* All benchmarks and logs can be monitored through **Android Logcat**.

---

## 🧑‍💻 Contributions

Pull requests are welcome. If you wish to contribute optimization techniques or additional PQC algorithms, feel free to fork and submit a PR.

---

## 📜 License

This project is open-source. Please refer to the `LICENSE` file for more details.


