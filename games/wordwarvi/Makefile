PORTNAME=	wordwarvi
PORTVERSION=	1.0.4
DISTVERSIONPREFIX=	v
PORTREVISION=	1
CATEGORIES=	games

MAINTAINER=	amdmi3@FreeBSD.org
COMMENT=	Side-scrolling shoot'em up '80s style arcade game
WWW=		https://smcameron.github.io/wordwarvi/

LICENSE=	GPLv2+ CC-BY-2.0 CC-BY-SA-3.0
LICENSE_COMB=	multi
LICENSE_FILE_GPLv2+ =	${WRKSRC}/COPYING

USE_GITHUB=	yes
GH_ACCOUNT=	smcameron

USES=		gmake gnome pkgconfig
USE_GNOME=	gtk20
MAKE_ENV=	SOURCE_DATE_EPOCH=0 BUILD_CC=${CC} BINDIR=${PREFIX}/bin

PORTDOCS=	AAA_HOW_TO_MAKE_NEW_LEVELS.txt AUTHORS README changelog.txt
PORTDATA=	*
PLIST_FILES=	bin/${PORTNAME} \
		share/man/man6/${PORTNAME}.6.gz

OPTIONS_DEFINE=	SOUND DOCS
OPTIONS_DEFAULT=SOUND

SOUND_LIB_DEPENDS=	libportaudio.so:audio/portaudio \
			libvorbisfile.so:audio/libvorbis
SOUND_MAKE_ARGS_OFF=	WITHAUDIO=no

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for f in ${PORTDOCS}
	${INSTALL_DATA} ${WRKSRC}/${f} ${STAGEDIR}${DOCSDIR}/
.endfor

.include <bsd.port.mk>
