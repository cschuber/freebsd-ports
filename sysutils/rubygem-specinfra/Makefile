PORTNAME=	specinfra
PORTVERSION=	2.82.16
CATEGORIES=	sysutils rubygems
MASTER_SITES=	RG

MAINTAINER=	naito.yuichiro@gmail.com
COMMENT=	Test suite for server configuration
WWW=		https://github.com/mizzy/specinfra

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

RUN_DEPENDS=	rubygem-net-scp>=0:security/rubygem-net-scp \
		rubygem-net-ssh>=2.7:security/rubygem-net-ssh \
		rubygem-net-telnet>=0:security/rubygem-net-telnet

USES=		gem

NO_ARCH=	yes

.include <bsd.port.mk>
