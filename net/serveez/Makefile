PORTNAME=	serveez
PORTVERSION=	0.2.2
PORTREVISION=	4
CATEGORIES=	net devel
MASTER_SITES=	GNU

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Server framework
WWW=		https://www.gnu.org/software/serveez/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

BROKEN_FreeBSD_13=	ld: error: duplicate symbol: guile_global_error
BROKEN_FreeBSD_14=	ld: error: duplicate symbol: guile_global_error

USES=		cpe guile:1.8 tar:xz libtool
CPE_VENDOR=	gnu
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--enable-libserveez-install
USE_LDCONFIG=	yes
INSTALL_TARGET=	install-strip

MAKE_JOBS_UNSAFE=	yes

INFO=		serveez

post-patch:
	@${REINPLACE_CMD} -e \
		'/^SUBDIRS/s|test||' ${WRKSRC}/Makefile.in
	@${REINPLACE_CMD} -e \
		'/date -r/s|^|#|' ${WRKSRC}/src/irc-server/Makefile.in
	@${ECHO_CMD} 'static char created[] = "2013-12-02 09:17 UTC";' \
		> ${WRKSRC}/src/irc-server/timestamp.c

.include <bsd.port.mk>
