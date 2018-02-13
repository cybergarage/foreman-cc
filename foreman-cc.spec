AutoReqProv: no

Name: foreman-cc
Version: %{expand:%%(git describe --abbrev=0 --tags)}
Release:	1%{?dist}
Summary: Foreman C++ library

Group: libs
License: BSD-3-clause
URL: https://github.com/cybergarage/foreman-cc

BuildRequires: python-devel, boost-devel, libsqlite3x-devel, automake
Requires: python

Source: %{expand:%%(pwd)}

%description
The C++ component of the Foreman system.


%prep
find . -mindepth 1 -delete
cp -af %{SOURCEURL0}/. .

%build
#export CFLAGS="$(pkg-config --cflags --libs python3) -Wall"
export CFLAGS="-Wall -O2"
export CXXFLAGS="-std=c++14 $CFLAGS"
export PYTHON_VERSION=3
%configure
make %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}


%files
%defattr(644,root,root,755)
/usr/lib64/libforeman++.a
/usr/include/foreman



%changelog
* Thu Jan 25 2018 Satoshi Konno <skonno@cybergarage.org>
- Initial packaging
