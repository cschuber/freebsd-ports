PORTNAME=	vxquery
PORTVERSION=	0.2.1
CATEGORIES=	security textproc
MASTER_SITES=	http://www.vuxml.org/files/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	VuXML Query Tool

LICENSE=	BSD2CLAUSE

USES=	tar:bzip2
USE_CXXSTD=	c++14

GNU_CONFIGURE=	yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/object/vxquery ${STAGEDIR}${PREFIX}/bin

.include <bsd.port.mk>
