PORTNAME=	lz4
PORTVERSION=	1.8.3
DISTVERSIONSUFFIX=	-1.el7
CATEGORIES=	archivers linux

MAINTAINER=	emulation@FreeBSD.org
COMMENT=	LZ4 compression library and utilities (Linux CentOS ${LINUX_DIST_VER})
WWW=		https://lz4.github.io/lz4/

USES=		cpe linux:c7
USE_LDCONFIG=	yes
USE_LINUX_RPM=	yes
CPE_VENDOR=	lz4_project

DESCR=		${.CURDIR}/../liblz4/pkg-descr

OPTIONS_DEFINE=	DOCS

.include <bsd.port.mk>
