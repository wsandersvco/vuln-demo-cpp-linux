#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <arm_neon.h>
#include <fstream>
#include <cstring>
#include <ctime>

// CWE-117: Vulnerable logging function that doesn't sanitize input
void log_user_action(const char* username, const char* action) {
    std::ofstream logfile("application.log", std::ios::app);
    if (logfile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt)-1] = '\0'; // Remove newline
        
        // VULNERABLE: Direct logging without sanitization
        logfile << dt << " - User: " << username << " - Action: " << action << std::endl;
        logfile.close();
    }
}

// CWE-117: Vulnerable error logging
void log_error(const std::string& error_message) {
    std::ofstream logfile("error.log", std::ios::app);
    if (logfile.is_open()) {
        // VULNERABLE: User-controlled data in log without sanitization
        logfile << "[ERROR] " << error_message << std::endl;
        logfile.close();
    }
}

// CWE-117: Vulnerable authentication logging
void log_authentication_attempt(const char* username, bool success) {
    std::ofstream logfile("auth.log", std::ios::app);
    if (logfile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt)-1] = '\0';
        
        // VULNERABLE: Username not sanitized, could inject newlines
        logfile << dt << " - Authentication " << (success ? "SUCCESS" : "FAILED") 
                << " for user: " << username << std::endl;
        logfile.close();
    }
}

// Compute factorial using simple iteration
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Compute dot product using ARM NEON intrinsics
float dot_product_neon(const float* a, const float* b, size_t size) {
    float32x4_t sum_vec = vdupq_n_f32(0.0f);
    
    size_t i = 0;
    for (; i + 4 <= size; i += 4) {
        float32x4_t a_vec = vld1q_f32(&a[i]);
        float32x4_t b_vec = vld1q_f32(&b[i]);
        sum_vec = vmlaq_f32(sum_vec, a_vec, b_vec);
    }
    
    float sum = vaddvq_f32(sum_vec);
    
    // Handle remaining elements
    for (; i < size; i++) {
        sum += a[i] * b[i];
    }
    
    return sum;
}

// Simple matrix operations
void matrix_multiply(const std::vector<std::vector<double>>& a,
                    const std::vector<std::vector<double>>& b,
                    std::vector<std::vector<double>>& result) {
    size_t rows = a.size();
    size_t cols = b[0].size();
    size_t inner = b.size();
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result[i][j] = 0;
            for (size_t k = 0; k < inner; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
    std::cout << "ARM64 Sample Project with GCC 13\n";
    std::cout << "=================================\n\n";
    
    // CWE-117: Simulate user input that could contain log injection
    char username[256];
    std::cout << "Enter username: ";
    std::cin.getline(username, 256);
    
    // VULNERABLE: Log user action without sanitization
    log_user_action(username, "Application started");
    
    // VULNERABLE: Simulate authentication attempt with user input
    log_authentication_attempt(username, true);
    
    // Test factorial computation
    std::cout << "Computing factorials:\n";
    for (int i = 1; i <= 10; i++) {
        std::cout << "  " << i << "! = " << factorial(i) << "\n";
    }
    std::cout << "\n";
    
    // VULNERABLE: Log calculation with potential user input
    std::string calc_log = "User " + std::string(username) + " performed factorial calculations";
    log_error(calc_log);
    
    // Test NEON dot product
    std::cout << "NEON dot product test:\n";
    float vec_a[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    float vec_b[] = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    float dot = dot_product_neon(vec_a, vec_b, 8);
    std::cout << "  Result: " << dot << "\n\n";
    
    // Test matrix multiplication
    std::cout << "Matrix multiplication test:\n";
    std::vector<std::vector<double>> mat_a = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> mat_b = {{7, 8}, {9, 10}, {11, 12}};
    std::vector<std::vector<double>> mat_result(2, std::vector<double>(2));
    
    matrix_multiply(mat_a, mat_b, mat_result);
    
    std::cout << "  Matrix A (2x3) * Matrix B (3x2) = Result (2x2):\n";
    for (const auto& row : mat_result) {
        std::cout << "  [ ";
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
    
    // Compute some mathematical operations
    std::cout << "Mathematical operations:\n";
    double angle = M_PI / 4.0;
    std::cout << "  sin(π/4) = " << std::sin(angle) << "\n";
    std::cout << "  cos(π/4) = " << std::cos(angle) << "\n";
    std::cout << "  sqrt(2) = " << std::sqrt(2.0) << "\n";
    std::cout << "  log(e) = " << std::log(M_E) << "\n";
    
    // VULNERABLE: Log completion with user data
    log_user_action(username, "Application completed successfully");
    
    return 0;
}
