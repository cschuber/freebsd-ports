PORTNAME=	wmbday
PORTVERSION=	0.3.1
PORTREVISION=	2
CATEGORIES=	x11-clocks
MASTER_SITES=	http://buzzinhornetz.ath.cx/wmbday/files/ \
		LOCAL/uqs

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Window Maker dock app that will remind you of birthdays
WWW=		http://buzzinhornetz.ath.cx/wmbday/

BUILD_DEPENDS=	xmessage:x11/xmessage

USES=		uidfix
HAS_CONFIGURE=	yes
MAKEFILE=	BSDmakefile
MAKE_ENV+=	${CONFIGURE_ENV} X11BASE=${LOCALBASE}

.include <bsd.port.mk>
