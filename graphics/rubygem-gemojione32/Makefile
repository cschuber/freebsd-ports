PORTNAME=	gemojione
PORTVERSION=	3.2.0
CATEGORIES=	graphics rubygems
MASTER_SITES=	RG
PKGNAMESUFFIX=	32

MAINTAINER=	mfechner@FreeBSD.org
COMMENT=	Gem containing EmojiOne unicode/image assets
WWW=		https://github.com/jonathanwiesel/gemojione

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

RUN_DEPENDS=	rubygem-json>=0:devel/rubygem-json

USES=		gem

NO_ARCH=	yes

PORTSCOUT=	limit:^3\.2\.

.include <bsd.port.mk>
