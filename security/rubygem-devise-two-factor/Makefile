PORTNAME=	devise-two-factor
PORTVERSION=	4.1.0
CATEGORIES=	security rubygems
MASTER_SITES=	RG

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Barebones two-factor authentication with Devise
WWW=		https://github.com/tinfoil/devise-two-factor

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	rubygem-activesupport50>=0<7.1:devel/rubygem-activesupport50 \
		rubygem-attr_encrypted>=1.3<5:security/rubygem-attr_encrypted \
		rubygem-devise>=4.0<5:devel/rubygem-devise \
		rubygem-railties50>=0<7.1:www/rubygem-railties50 \
		rubygem-rotp>=6.0<7:devel/rubygem-rotp

USES=		gem

NO_ARCH=	yes

PORTSCOUT=	ignore:1

.include <bsd.port.mk>
