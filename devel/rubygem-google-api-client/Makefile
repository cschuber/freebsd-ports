PORTNAME=	google-api-client
PORTVERSION=	0.53.0
CATEGORIES=	devel rubygems
MASTER_SITES=	RG

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Client for accessing Google APIs
WWW=		https://github.com/googleapis/google-api-ruby-client

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	rubygem-google-apis-core>=0.1<1:devel/rubygem-google-apis-core \
		rubygem-google-apis-generator>=0.1<1:devel/rubygem-google-apis-generator

USES=		gem

NO_ARCH=	yes

.include <bsd.port.mk>
