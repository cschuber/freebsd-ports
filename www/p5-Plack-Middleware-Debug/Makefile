PORTNAME=	Plack-Middleware-Debug
PORTVERSION=	0.18
PORTREVISION=	1
CATEGORIES=	www perl5
MASTER_SITES=	CPAN
MASTER_SITE_SUBDIR=	CPAN:MIYAGAWA
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Perl extension to display information about current request/response
WWW=		https://metacpan.org/release/Plack-Middleware-Debug

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Class-Method-Modifiers>=1.05:devel/p5-Class-Method-Modifiers \
		p5-Data-Dump>=0:devel/p5-Data-Dump \
		p5-File-ShareDir>=1.00:devel/p5-File-ShareDir \
		p5-Plack>=0:www/p5-Plack \
		p5-Text-MicroTemplate>=0.15:textproc/p5-Text-MicroTemplate \
		p5-Module-Versions>=0.01:devel/p5-Module-Versions
TEST_DEPENDS=	p5-Test-Requires>=0:devel/p5-Test-Requires

USES=		perl5
USE_PERL5=	modbuildtiny

NO_ARCH=	yes

.include <bsd.port.mk>
