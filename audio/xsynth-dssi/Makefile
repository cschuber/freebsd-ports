PORTNAME=	xsynth-dssi
PORTVERSION=	0.9.4
PORTREVISION=	7
CATEGORIES=	audio
MASTER_SITES=	SF/dssi/${PORTNAME}/${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Classic analog style software synthesizer
WWW=		http://dssi.sourceforge.net/download.html

BUILD_DEPENDS=	${LOCALBASE}/include/dssi.h:audio/dssi \
		${LOCALBASE}/include/ladspa.h:audio/ladspa
LIB_DEPENDS=	libdssialsacompat.so:audio/libdssialsacompat \
		liblo.so:audio/liblo \
		libjack.so:audio/jack

LICENSE=	GPLv2 LGPL21
LICENSE_COMB=	multi

GNU_CONFIGURE=	yes
USE_GNOME=	gtk20
USES=		gmake gnome libtool pkgconfig
INSTALL_TARGET=	install-strip

CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

.include <bsd.port.mk>
