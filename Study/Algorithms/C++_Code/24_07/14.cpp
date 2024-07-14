// 2884 알람 시계
// 조건문

#include <cstdio>

int main() {
    int h, m;
    scanf("%d %d", &h, &m);

    if (m - 45 < 0) {
        if (h - 1 < 0) {
            h = 24 - 1;    
        } else {
            h -= 1;
        }        
        int x = 45 - m;
        m = 60 - x;
    } else {
        m -= 45;
    }
    printf("%d %d", h, m);

    return 0;
}
/* 
#include <iostream>

int main() {
    int H, M;
    std::cin >> H >> M;

    // 45분 일찍 설정
    M -= 45;
    if (M < 0) {
        M += 60;
        H--;
        if (H < 0) {
            H = 23;
        }
    }

    std::cout << H << " " << M << std::endl;
    return 0;
}
 */
/* todo : 단위테스트 후 이해.
#include <iostream>
#include <chrono>

int main() {
    int H, M;
    std::cin >> H >> M;

    // 현재 시간인 H시 M분을 minutes 단위로 변환
    std::chrono::minutes current_time = std::chrono::hours(H) + std::chrono::minutes(M);

    // 45분 일찍 알람 설정
    std::chrono::minutes early_alarm = current_time - std::chrono::minutes(45);

    // 새로운 시간을 시간과 분 단위로 변환
    int new_H = (early_alarm.count() / 60) % 24;
    int new_M = early_alarm.count() % 60;

    // 음수 시간이 나올 경우 24시간 체계로 변환
    if (new_H < 0) {
        new_H += 24;
    }
    if (new_M < 0) {
        new_M += 60;
    }

    std::cout << new_H << " " << new_M << std::endl;

    return 0;
}
 */