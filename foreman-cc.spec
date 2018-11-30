Name: foreman-cc
Version: %{expand:%%(git describe --abbrev=0 --tags)}
Release:	%{_sd_build_id}%{?dist}
Summary: Foreman C++ library

Group: libs
License: BSD-3-clause
URL: https://github.com/cybergarage/foreman-cc

BuildRequires: automake, sqlite-devel, curl-devel, libuuid-devel
Requires: sqlite3, libuuid

Source: %{expand:%%(pwd)}

%description
The C++ component of the Foreman system.


%prep
find . -mindepth 1 -delete
cp -af %{SOURCEURL0}/. .

%build
#export CFLAGS="$(pkg-config --cflags --libs python3) -Wall"
#export PYTHON_VERSION=3
%configure_centos
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
