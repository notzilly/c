#include "tela.h"
#include <X11/Xlib.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

/* Ajustar de acordo com o servidor X, para acertar as cores */
#define VINTE_E_QUATRO
#ifdef VINTE_E_QUATRO
#define B_R 8
#define B_G 8
#define B_B 8
#else
#define B_R 5
#define B_G 6
#define B_B 5
#endif

#define XPC (600/TELA_LARG)
#define YPC (800/TELA_ALT)

// conversao de coordenadas entre tela e canvas
int ttocx(float x)
{
    return x * XPC;
}

int ttocy(float y)
{
    return y * YPC;
}

float ctotx(int x)
{
    return (float)x / XPC;
}

float ctoty(int y)
{
    return (float)y / YPC;
}


struct {
    Display *display;
    unsigned int screen;
    Window janela;
    Pixmap pixmap;
    GC gc;

    retangulo ret_tela;
    long cor;
    long cor_fundo;
    rato rato;
    int teclas[4];
    int nteclas;
} t;

// os eventos que queremos receber do servidor X
#define EVENT_MASK (ButtonPressMask | ButtonReleaseMask | PointerMotionMask \
                    | KeyPressMask | KeyReleaseMask)

// declara funções privadas
void tela_inicializa_display(void);
void tela_inicializa_janela(void);
void tela_inicializa_contexto(void);
void tela_inicializa_funcoes(void);
void tela_mostra_janela(void);
void rem_tecla(int tec);
void ins_tecla(int tec);
void tela_processa_eventos(void);


void rem_tecla(int tec)
{
    int i;
    for (i=0; i<4; i++) {
        if (t.teclas[i] == tec) {
            int j;
            if (i < t.nteclas) {
                t.nteclas--;
            }
            t.teclas[i] = 0;
            for (j=i+1; j<4; j++) {
                t.teclas[j-1] = t.teclas[j];
            }
        }
    }
}

void ins_tecla(int tec)
{
    int j;
    rem_tecla(tec);
    for (j=0; j<3; j++) {
        t.teclas[4-j-1] = t.teclas[4-j-2];
    }
    t.teclas[0] = tec;
    if (t.nteclas < 4) {
        t.nteclas++;
    }
}

// Construtor da tela.
void tela_inicializa(void)
{
    tela_inicializa_display();
    tela_inicializa_janela();
    tela_inicializa_contexto();
    tela_inicializa_funcoes();

    tela_mostra_janela();
    tela_atualiza();
}

// Destrutor da tela.
void tela_finaliza(void)
{
    XFreePixmap(t.display, t.pixmap);
    XCloseDisplay(t.display);
}

// Inicializa display, estabelecendo conexão com servidor X.
void tela_inicializa_display(void)
{
    // Estabelece conexão com servidor X.
    // O argumento indica o nome do display (se for NULL, 
    // utiliza-se o valor da variável de ambiente DISPLAY).
    t.display = XOpenDisplay(NULL);
    assert(t.display != NULL);

    // Obtém o número do screen default deste display.  
    t.screen = DefaultScreen(t.display);
}

// Inicializa janela, definindo seus atributos.
void tela_inicializa_janela(void)
{
    unsigned long mask = 0L;
    XSetWindowAttributes attr;

    // Define atributos da janela a ser criada.

    // os eventos que queremos receber do servidor X
    attr.event_mask = EVENT_MASK;
    attr.background_pixel = WhitePixel(t.display, t.screen);
    attr.backing_store = Always;
    attr.save_under = True;
    mask = CWEventMask | CWBackPixel | CWBackingStore | CWSaveUnder;

    t.ret_tela.cse.x = 0;
    t.ret_tela.cse.y = 0;
    t.ret_tela.cid.x = TELA_LARG;
    t.ret_tela.cid.y = TELA_ALT;
    // Cria janela.    
    t.janela = XCreateWindow(t.display, RootWindow(t.display, t.screen),
                              0, 0,	// coordenadas do canto superior esquerdo
			      ttocx(TELA_LARG), ttocy(TELA_ALT),	// dimensões internas
			      0,	// número de pixels da borda da janela
			      0,	// profundidade da janela
			      InputOutput,	// classe da janela
			      (Visual *) CopyFromParent,	// tipo de visual
			      mask,	// máscara que indica os atributos de attr
			      &attr);	// conjunto de atributos da janela

    // Cria área onde desenhar o conteúdo da janela
    t.pixmap = XCreatePixmap(t.display, RootWindow(t.display, t.screen),
		             ttocx(TELA_LARG), ttocy(TELA_ALT),
		             DefaultDepth(t.display, t.screen));

    // Define nome para a janela.
    XStoreName(t.display, t.janela, "tela");
}

// Inicializa o contexto gráfico.
void tela_inicializa_contexto(void)
{
    assert(t.display != NULL);

    t.gc = XCreateGC(t.display, t.janela, 0, NULL);
    t.cor = WhitePixel(t.display, t.screen);
    XSetForeground(t.display, t.gc, t.cor);
    t.cor_fundo = BlackPixel(t.display, t.screen);
    XSetBackground(t.display, t.gc, t.cor_fundo);
    XSetLineAttributes(t.display, t.gc, 1, LineSolid, CapRound,
		       JoinRound);
}

// Inicializa o rato e as funções.
void tela_inicializa_funcoes(void)
{
    assert(t.display != NULL);

    t.rato.posicao.x = 0;
    t.rato.posicao.y = 0;
    t.rato.botao[0] = false;
    t.rato.botao[1] = false;
    t.rato.botao[2] = false;
    t.rato.botao[3] = false;
    t.rato.botao[4] = false;
    t.rato.mudou = -1;

    t.nteclas = 0;
}

// Mostra janela.
void tela_mostra_janela(void)
{
    // Mapeia a janela no display para torná-la visível.
    XMapWindow(t.display, t.janela);
}

// Atualiza tela.
void tela_atualiza(void)
{
    tela_processa_eventos();
    XCopyArea(t.display, t.pixmap, t.janela, t.gc,
              ttocx(t.ret_tela.cse.x), ttocy(t.ret_tela.cse.y), 
              ttocx(t.ret_tela.cid.x)-ttocx(t.ret_tela.cse.x), 
              ttocy(t.ret_tela.cid.y)-ttocy(t.ret_tela.cse.y), 0, 0);
    XFlush(t.display);
}

#define AJEITA(x) (x < 0 ? 0 : (x > 1 ? 1 : x))
#define COMP(x, X) ((int)(AJEITA(x) * ((1<<X)-1)))
#define COR(r, g, b, R, G, B) ((COMP(r,R)<<(G+B)) | (COMP(g,G)<<B) | COMP(b,B))
long calcula_cor(cor cor)
{
    return COR(cor.r, cor.g, cor.b, B_R, B_G, B_B);
}

void tela_cor(cor cor)
{
    t.cor = calcula_cor(cor);
    XSetForeground(t.display, t.gc, t.cor);
}

void tela_cor_fundo(cor cor)
{
    t.cor_fundo = calcula_cor(cor);
    XSetForeground(t.display, t.gc, t.cor_fundo);
}


void tela_limpa(void)
{
    XSetForeground(t.display, t.gc, t.cor_fundo);
    tela_retangulo(t.ret_tela);
    XSetForeground(t.display, t.gc, t.cor);
}

/* desenha uma linha da ponto p1 ate p2, na cor atual */
void tela_linha(ponto p1, ponto p2)
{
    XDrawLine(t.display, t.pixmap, t.gc, ttocx(p1.x), ttocy(p1.y),
                                         ttocx(p2.x), ttocy(p2.y));
}


/* preenche um retangulo na posição pos com tamanho tam com a cor atual */
void tela_retangulo(retangulo ret)
{
    XFillRectangle(t.display, t.pixmap, t.gc,
		   ttocx(ret.cse.x), ttocy(ret.cse.y), 
                   ttocx(ret.cid.x)-ttocx(ret.cse.x), 
                   ttocy(ret.cid.y)-ttocy(ret.cse.y));
}

void tela_circulo(circulo circ)
{
    tela_arco(circ, 0, 360);
}

float corrige_angulo(float a)
{
    while (a>360) a -= 360;
    while (a<0) a += 360;
    return a;
}

void tela_arco(circulo circ, float angulo1, float angulo2)
{
    angulo2=corrige_angulo(angulo2);
    angulo1=corrige_angulo(angulo1);
    if (angulo2 < angulo1) angulo2 += 360;
    XFillArc(t.display, t.pixmap, t.gc, ttocx(circ.centro.x - circ.raio),
                                        ttocy(circ.centro.y - circ.raio),
                                        ttocx(2 * circ.raio), ttocy(2 * circ.raio),
                                        angulo1 * 64, (angulo2-angulo1) * 64);
}

void tela_texto(ponto pos, char s[])
{
    XDrawString(t.display, t.pixmap, t.gc, 
                ttocx(pos.x), ttocy(pos.y)+10,
                s, strlen(s));
}

rato tela_rato(void)
{
    return t.rato;
}

int tela_teclas_apertadas(int v[4])
{
    int i;
    int r;
    for (i=0; i<4; i++) {
        v[i] = t.teclas[i];
    }
    r = t.nteclas;
    t.nteclas = 0;
    return r;
}


void tela_processa_eventos(void)
{
    XEvent evento;
    XButtonEvent *be = (XButtonEvent *) & evento;
    XMotionEvent *me = (XMotionEvent *) & evento;
    XKeyEvent *ke = (XKeyEvent *) & evento;

    while (XCheckMaskEvent(t.display, EVENT_MASK, &evento) == True) {
	switch (evento.type) {
	case ButtonPress:
	    t.rato.mudou = be->button - 1;
	    t.rato.botao[t.rato.mudou] = 1;
	    break;
	case ButtonRelease:
	    t.rato.mudou = be->button - 1;
	    t.rato.botao[t.rato.mudou] = 0;
	    break;
	case MotionNotify:
	    t.rato.mudou = -1;
	    t.rato.posicao.x = me->x;
	    t.rato.posicao.y = me->y;
	    break;
	case KeyPress:
            ins_tecla(XLookupKeysym(ke, 0));
	    break;
	case KeyRelease:
            rem_tecla(XLookupKeysym(ke, 0));
	}
    }
}

