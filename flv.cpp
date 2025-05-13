#include <windows.h>
#include <cmath>
#include <ctime>

// Aviso inicial
bool mostrarAviso() {
    int resposta = MessageBox(
        NULL,
        L"!!AVISO!!\nEste \"Malware\" no final pode prejudicar seu computador (caso versão não segura)\ne contém cores piscantes.\n\nTem certeza que deseja continuar?",
        L"AVISO DE SEGURANÇA",
        MB_ICONWARNING | MB_YESNO
    );
    return resposta == IDYES;
}

// Bytebeat simples
void tocarBytebeat() {
    static int t = 0;
    Beep(((t * (t >> 5 | t >> 8)) >> (t >> 16)) & 127, 15);
    t++;
}

// Efeito 1
VOID WINAPI ci(int x, int y, int w, int h) {
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
    tocarBytebeat();
}
void efeitoCi() {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    DWORD start = GetTickCount();
    while (GetTickCount() - start < 5000) {
        int x = rand() % (w + 1000) - 500;
        int y = rand() % (h + 1000) - 500;
        for (int i = 0; i < 1000; i += 100) {
            ci(x - i / 2, y - i / 2, i, i);
        }
    }
}

// Efeito 2
void elipseRebote() {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int x = 10, y = 10, dx = 20, dy = 20;
    DWORD start = GetTickCount();
    while (GetTickCount() - start < 5000) {
        HDC hdc = GetDC(0);
        x += dx; y += dy;
        if (x <= 0 || x >= w - 100) dx = -dx;
        if (y <= 0 || y >= h - 100) dy = -dy;

        HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SelectObject(hdc, brush);
        Ellipse(hdc, x, y, x + 100, y + 100);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
        tocarBytebeat();
        Sleep(1);
    }
}

// Efeito 3
void pieEffect() {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    DWORD start = GetTickCount();
    while (GetTickCount() - start < 5000) {
        HDC hdc = GetDC(0);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SelectObject(hdc, brush);
        Pie(hdc, rand() % w, rand() % h, rand() % w, rand() % h,
            rand() % w, rand() % h, rand() % w, rand() % h);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
        tocarBytebeat();
        Sleep(1);
    }
}

// Efeito 4
void setpixel_1() {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    DWORD start = GetTickCount();

    while (GetTickCount() - start < 5000) {
        HDC hdc = GetDC(0);
        for (int y = 0; y < h; y += 5) {
            for (int x = 0; x < w; x += 5) {
                int r = rand() % 256;
                int g = rand() % 256;
                int b = rand() % 256;
                SetPixel(hdc, x, y, RGB(r, g, b));
            }
        }
        ReleaseDC(0, hdc);
        tocarBytebeat();
        Sleep(1);
    }
}

// Efeito 5
void efeitoBitBlt() {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    DWORD start = GetTickCount();

    while (GetTickCount() - start < 5000) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 10, 10, w, h, hdc, 12, 12, SRCPAINT);
        ReleaseDC(0, hdc);
        tocarBytebeat();
        Sleep(10);
    }
}

// Efeito final infinito
void efeitoFinalPatBlt() {
    int x = GetSystemMetrics(0);
    int y = GetSystemMetrics(1);
    HDC hdc;

    while (1) {
        tocarBytebeat();
        hdc = GetDC(0);
        PatBlt(hdc, 0, 0, x, y, PATINVERT);
        Sleep(100);
        ReleaseDC(0, hdc);
    }
}

// Efeito StretchBlt
void efeitoStretchBlt() {
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    HDC desk;
    DWORD start = GetTickCount();

    while (GetTickCount() - start < 5000) {
        desk = GetDC(0);
        StretchBlt(desk, 0, -20, sw, sh + 40, desk, 0, 0, sw, sh, SRCCOPY);
        ReleaseDC(0, desk);
        Sleep(4);
    }
}

// Função para apagar a tela
void apagarTela() {
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(0);
    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
    RECT rect = { 0, 0, sw, sh };
    FillRect(hdc, &rect, black);
    ReleaseDC(0, hdc);
    DeleteObject(black);
}

int main() {
    srand(time(0));
    if (!mostrarAviso()) return 0;

    // Aplica os efeitos
    efeitoCi();
    elipseRebote();
    pieEffect();
    setpixel_1();
    efeitoBitBlt();
    efeitoFinalPatBlt();

    // Aplica o efeito StretchBlt
    efeitoStretchBlt();

    // Apaga a tela
    apagarTela();

    // Aguarda 1 minuto (60.000 ms)
    Sleep(60000);

    // Força o desligamento do computador (causando a tela de reparo ao reiniciar)
    system("shutdown /s /f /t 0");

    return 0;
}
