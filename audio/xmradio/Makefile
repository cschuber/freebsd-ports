PORTNAME=	xmradio
PORTVERSION=	1.2
PORTREVISION=	3
CATEGORIES=	audio
MASTER_SITES=	https://BSDforge.com/projects/source/audio/xmradio/

MAINTAINER=	portmaster@BSDforge.com
COMMENT=	Motif based FM tuner (for use with bktr(4) driver)
WWW=		https://BSDforge.com/projects/audio/xmradio/

LICENSE=	BSD2CLAUSE

DEPRECATED=     Requires defunct bktr
EXPIRATION_DATE=2023-12-31
.if !exists(/usr/include/dev/bktr/ioctl_bt848.h)
IGNORE=		needs bktr(4) which is no longer available on your FreeBSD version
.endif
ONLY_FOR_ARCHS=	i386 amd64 powerpc64

USES=		imake motif xorg
USE_XORG=	ice sm x11 xext xmu xpm xt

PLIST_FILES=	bin/xmradio lib/X11/app-defaults/XMradio

.include <bsd.port.mk>
